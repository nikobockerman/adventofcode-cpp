#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <optional>
#include <stack>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "convert.hpp"
#include "program.hpp"
#include "utils.hpp"

using namespace std::string_literals;

namespace {

using Crate = char;
using Stack = std::stack<Crate>;

class Move {
 public:
  static constexpr std::size_t inputIndexOffset{1};

  Move(std::size_t amount, std::size_t inputIndexFromStack,
       std::size_t inputIndexToStack)
      : _amount{amount},
        _indexFromStack{inputIndexFromStack - inputIndexOffset},
        _indexToStack{inputIndexToStack - inputIndexOffset} {
    if (_amount == 0) {
      throw std::runtime_error("Move without amount");
    }
  }

  [[nodiscard]] auto amount() const { return _amount; }
  [[nodiscard]] auto indexFromStack() const { return _indexFromStack; }
  [[nodiscard]] auto indexToStack() const { return _indexToStack; }

 private:
  std::size_t _amount;
  std::size_t _indexFromStack;
  std::size_t _indexToStack;
};

class Stage {
 public:
  Stage(std::vector<Stack> stacks) : _stacks{std::move(stacks)} {}

  [[nodiscard]] auto stacks() const -> auto & { return _stacks; }

  [[nodiscard]] auto applyMove(const Move &move) const -> Stage;

 private:
  std::vector<Stack> _stacks;

  [[nodiscard]] auto applySingleMove(auto indexFrom, auto indexTo) const
      -> Stage {
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
    return {std::move(newStacks)};
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

[[nodiscard]] auto Stage::applyMove(const Move &move) const -> Stage {
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

auto parseCrate(auto crateChar) -> std::optional<Crate> {
  if (crateChar == ' ') {
    return std::nullopt;
  }
  return crateChar;
}

auto countStacks(auto stackIdLine) -> std::size_t {
  return std::count_if(stackIdLine.begin(), stackIdLine.end(),
                       [](char character) { return character != ' '; });
}

auto crateCharIndex(auto stackIndex) { return 1 + 4 * stackIndex; }

auto loadStage(auto lines) -> Stage {
  auto stackCount = countStacks(lines.back());

  std::vector<Stack> stacks{};
  stacks.reserve(stackCount);

  for (std::size_t index{}; index < stackCount; ++index) {
    stacks.emplace_back(std::accumulate(
        lines.rbegin() + 1, lines.rend(), Stack{},
        [index](auto stack, auto line) {
          auto crate = parseCrate(line.at(crateCharIndex(index)));
          if (crate) {
            stack.push(*crate);
          }
          return stack;
        }));
  }
  return {std::move(stacks)};
}

auto splitMoveLine(auto str) { return split(str, ' '); }

auto parseMove(std::string_view line) {
  constexpr std::size_t expectedPartsSize{6};
  constexpr auto indexMoveStr{0};
  constexpr auto indexFromStr{2};
  constexpr auto indexToStr{4};

  auto parts = splitMoveLine(line);
  if (parts.size() != expectedPartsSize || parts.at(indexMoveStr) != "move" ||
      parts.at(indexFromStr) != "from" || parts.at(indexToStr) != "to") {
    throw std::runtime_error("Unexpected move line");
  }

  constexpr auto indexAmount{1};
  constexpr auto indexFrom{3};
  constexpr auto indexTo{5};
  return Move{convert<std::size_t>(parts.at(indexAmount)),
              convert<std::size_t>(parts.at(indexFrom)),
              convert<std::size_t>(parts.at(indexTo))};
}

auto loadMoves(auto lines) {
  std::vector<Move> moves;
  std::transform(lines.begin(), lines.end(), std::back_inserter(moves),
                 [](auto line) { return parseMove(line); });
  return moves;
}

auto splitInputParts(auto &lines) -> std::tuple<std::vector<std::string_view>,
                                                std::vector<std::string_view>> {
  auto parts = split(lines, [](auto line) { return line.empty(); });
  if (parts.size() != 2) {
    throw std::runtime_error("Incorrect parts");
  }
  return {std::move(parts.at(0)), std::move(parts.at(1))};
}

auto _main(auto input) {
  auto lines = split(input, '\n');
  auto [stageLines, moveLines] = splitInputParts(lines);
  auto stage = loadStage(stageLines);
  auto moves = loadMoves(moveLines);

  spdlog::info("Initial stage: {}", stage);
  auto finalStage = std::accumulate(
      moves.begin(), moves.end(), stage,
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
