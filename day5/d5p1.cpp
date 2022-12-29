#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <optional>
#include <ranges>
#include <stack>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "convert.hpp"
#include "program.hpp"
#include "utils.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace ranges = std::ranges;
namespace views = std::views;

namespace {

using Crate = char;
using Stack = std::stack<Crate>;

class Move {
 public:
  static constexpr std::size_t inputIndexOffset{1};

  constexpr Move(std::size_t amount, std::size_t inputIndexFromStack,
                 std::size_t inputIndexToStack)
      : _amount{amount},
        _indexFromStack{inputIndexFromStack - inputIndexOffset},
        _indexToStack{inputIndexToStack - inputIndexOffset} {
    if (_amount == 0) {
      throw std::runtime_error("Move without amount");
    }
  }

  [[nodiscard]] constexpr auto amount() const { return _amount; }
  [[nodiscard]] constexpr auto indexFromStack() const {
    return _indexFromStack;
  }
  [[nodiscard]] constexpr auto indexToStack() const { return _indexToStack; }

 private:
  std::size_t _amount;
  std::size_t _indexFromStack;
  std::size_t _indexToStack;
};

constexpr auto constructStacks(auto &&stacksView) -> std::vector<Stack> {
  auto stacks = std::vector<Stack>{};
  for (auto stackView : stacksView) {
    auto commonStackView = stackView | views::common;
    stacks.emplace_back(commonStackView.begin(), commonStackView.end());
  }
  return stacks;
}

class Stage {
 public:
  constexpr explicit Stage(auto &&stacksView)
      : _stacks{constructStacks(std::move(stacksView))} {}

  constexpr explicit Stage(std::vector<Stack> stacks)
      : _stacks{std::move(stacks)} {}

  [[nodiscard]] constexpr auto stacks() const -> auto & { return _stacks; }

  [[nodiscard]] constexpr auto applyMove(const Move &move) const -> Stage;

 private:
  std::vector<Stack> _stacks;

  [[nodiscard]] constexpr auto applySingleMove(auto indexFrom,
                                               auto indexTo) const -> Stage {
    auto &fromStack = _stacks.at(indexFrom);
    if (fromStack.empty()) {
      throw std::runtime_error("Moving from empty stack");
    }

    Crate movedCrate{fromStack.top()};

    std::vector<Stack> newStacks;
    for (decltype(_stacks)::size_type i{}; i < _stacks.size(); ++i) {
      if (i == indexFrom) {
        Stack stack{_stacks.at(i)};
        stack.pop();
        newStacks.push_back(std::move(stack));
      } else if (i == indexTo) {
        Stack stack{_stacks.at(i)};
        stack.push(movedCrate);
        newStacks.push_back(std::move(stack));
      } else {
        newStacks.emplace_back(_stacks.at(i));
      }
    }
    return Stage{std::move(newStacks)};
  }
};

}  // namespace

namespace fmt {

template <>
struct formatter<Stack> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) const {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const Stack &stack, FormatContext &ctx) const {
    if (stack.empty()) {
      return format_to(ctx.out(), "Empty");
    }
    return format_to(ctx.out(), "[{}:{}]", stack.size(), stack.top());
  }
};

template <>
struct formatter<Stage> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) const {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const Stage &stage, FormatContext &ctx) const {
    return format_to(ctx.out(), "{}", fmt::join(stage.stacks(), ","));
  }
};

template <>
struct formatter<Move> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) const {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const Move &move, FormatContext &ctx) const {
    return format_to(ctx.out(), "{} from {} to {}", move.amount(),
                     move.indexFromStack() + Move::inputIndexOffset,
                     move.indexToStack() + Move::inputIndexOffset);
  }
};

}  // namespace fmt

namespace {

[[nodiscard]] constexpr auto Stage::applyMove(const Move &move) const -> Stage {
  std::optional<Stage> result;
  const Stage *current{this};
  for (auto i = move.amount(); i > 0; --i) {
    result =
        current->applySingleMove(move.indexFromStack(), move.indexToStack());
    current = &result.value();
    spdlog::debug("Intermediate stage: {}", *current);
  }
  return result.value();
}

constexpr auto countStacks(auto &&stackIdLine) -> std::size_t {
  return ranges::count_if(stackIdLine,
                          [](auto character) { return character != ' '; });
}

constexpr auto crateCharIndex(auto stackIndex) { return 1 + 4 * stackIndex; }

constexpr auto loadStage(auto &&linesView) -> Stage {
  auto &&linesCommonView = linesView | views::common;
  auto lines = std::vector(linesCommonView.begin(), linesCommonView.end());
  auto stackCount = countStacks(lines.back());
  spdlog::debug("Stack count: {}", stackCount);

  auto crateLinesView = lines | views::reverse | views::drop(1);
  const auto crateLines =
      std::vector(crateLinesView.begin(), crateLinesView.end());
  const auto crateLinesCount = crateLines.size();

  auto stacksView =
      views::iota(std::size_t{}, stackCount) |
      views::transform([](auto counter) { return crateCharIndex(counter); }) |
      views::transform([crateLinesCount, &crateLines](auto index) {
        return crateLines | views::transform([index](const auto &line) {
                 return *ranges::next(line.begin(), index);
               }) |
               views::take_while(
                   [](auto crateChar) { return crateChar != ' '; }) |
               views::transform(
                   [](auto crateChar) { return Crate{crateChar}; });
      });

  return Stage{std::move(stacksView)};
}

constexpr auto parseMove(auto &&line) {
  constexpr auto indexAmount{1};
  constexpr auto indexFrom{3};
  constexpr auto indexTo{5};

  auto parts = line | views::split(" "sv);
  return Move{convert<std::size_t>(*ranges::next(parts.begin(), indexAmount)),
              convert<std::size_t>(*ranges::next(parts.begin(), indexFrom)),
              convert<std::size_t>(*ranges::next(parts.begin(), indexTo))};
}

constexpr auto loadMoves(auto &&lines) {
  return lines | views::transform([](auto &&line) {
           spdlog::debug("DEBUG");
           spdlog::debug("Parsing move: {}", line);
           return parseMove(line);
         });
}

auto _main(std::string_view input) {
  auto &&partsView =
      input | views::split("\n\n"sv) | views::transform([](auto part) {
        return part | views::split("\n"sv) |
               views::take_while([](auto line) { return !line.empty(); });
      });
  auto parts = std::vector(partsView.begin(), partsView.end());
  if (parts.size() != 2) {
    throw std::runtime_error("Incorrect parts");
  }

  auto stage = loadStage(parts.at(0) | views::all);
  auto moves = loadMoves(parts.at(1) | views::all) | views::common;

  spdlog::info("Initial stage: {}", stage);
  auto finalStage = std::accumulate(
      moves.begin(), moves.end(), std::move(stage),
      [](const auto &prev, const auto &move) {
        spdlog::debug("Performing move ({}); Stage: {}", move, prev);
        auto next = prev.applyMove(move);
        spdlog::debug("Move performed ({}); Stage: {}", move, next);
        return next;
      });

  const auto &stacks = finalStage.stacks();
  return std::accumulate(
      stacks.begin(), stacks.end(), ""s,
      [](const auto &prev, const auto &stack) { return prev + stack.top(); });
}

}  // namespace

SHARED_MAIN
