#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "common.hpp"
#include "input.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace ranges = std::ranges;
namespace views = std::views;

namespace {

using Crate = char;
using Stack = std::vector<Crate>;

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

class Stage {
 public:
  constexpr explicit Stage(auto &&stacksView)
      : _stacks{stacksView | ranges::to<std::vector<Stack>>()} {}

  constexpr explicit Stage(std::vector<Stack> stacks)
      : _stacks{std::move(stacks)} {}

  [[nodiscard]] constexpr auto stacks() const -> auto & { return _stacks; }

  [[nodiscard]] RUNTIME_CONSTEXPR auto applyMove(const Move &move) const
      -> Stage;

 private:
  std::vector<Stack> _stacks;

  [[nodiscard]] constexpr auto applySingleMove(auto indexFrom,
                                               auto indexTo) const -> Stage {
    auto &fromStack = _stacks.at(indexFrom);
    if (fromStack.empty()) {
      throw std::runtime_error("Moving from empty stack");
    }

    Crate movedCrate{fromStack.back()};

    std::vector<Stack> newStacks;
    for (decltype(_stacks)::size_type i{}; i < _stacks.size(); ++i) {
      if (i == indexFrom) {
        Stack stack{_stacks.at(i)};
        stack.pop_back();
        newStacks.emplace_back(std::move(stack));
      } else if (i == indexTo) {
        Stack stack{_stacks.at(i)};
        stack.emplace_back(movedCrate);
        newStacks.emplace_back(std::move(stack));
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
      return fmt::format_to(ctx.out(), "Empty");
    }
    return fmt::format_to(ctx.out(), "[{}:{}]", stack.size(), stack.back());
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
    return fmt::format_to(ctx.out(), "{}", fmt::join(stage.stacks(), ","sv));
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
    return fmt::format_to(ctx.out(), "{} from {} to {}", move.amount(),
                          move.indexFromStack() + Move::inputIndexOffset,
                          move.indexToStack() + Move::inputIndexOffset);
  }
};

}  // namespace fmt

namespace {

[[nodiscard]] RUNTIME_CONSTEXPR auto Stage::applyMove(const Move &move) const
    -> Stage {
  std::optional<Stage> result;
  const Stage *current{this};
  for (auto i = move.amount(); i > 0; --i) {
    result =
        current->applySingleMove(move.indexFromStack(), move.indexToStack());
    current = &result.value();
    logd("Intermediate stage: {}", *current);
  }
  return result.value();
}

constexpr auto countStacks(auto &&stackIdLine) -> std::size_t {
  return ranges::count_if(stackIdLine,
                          [](auto character) { return character != ' '; });
}

constexpr auto crateCharIndex(auto stackIndex) { return 1 + 4 * stackIndex; }

RUNTIME_CONSTEXPR auto loadStage(auto &&linesView) -> Stage {
  auto &&linesCommonView = linesView | views::common;
  auto lines = std::vector(linesCommonView.begin(), linesCommonView.end());
  auto stackCount = countStacks(lines.back());
  logd("Stack count: {}", stackCount);

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

RUNTIME_CONSTEXPR auto loadMoves(auto &&lines) {
  return lines | views::transform([](auto &&line) {
           logd("DEBUG");
           logd("Parsing move: {}", line);
           return parseMove(line);
         });
}

RUNTIME_CONSTEXPR auto solve() {
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

  logi("Initial stage: {}", stage);
  auto finalStage =
      std::accumulate(moves.begin(), moves.end(), std::move(stage),
                      [](const auto &prev, const auto &move) {
                        logd("Performing move ({}); Stage: {}", move, prev);
                        auto next = prev.applyMove(move);
                        logd("Move performed ({}); Stage: {}", move, next);
                        return next;
                      });

  const auto &stacks = finalStage.stacks();
  return std::accumulate(
      stacks.begin(), stacks.end(), ""s,
      [](const auto &prev, const auto &stack) { return prev + stack.back(); });
}

}  // namespace

auto main() -> int {
  enableDebugLogging();
  RUNTIME_CONSTEXPR auto result = solve();
  printResult(result);
  return 0;
}
