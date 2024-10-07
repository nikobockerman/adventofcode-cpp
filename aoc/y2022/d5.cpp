#include <fmt/base.h>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "convert.hpp"
#include "day-interface.hpp"
#include "named-type.hpp"
#include "result-type.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_literals;
using namespace std::string_view_literals;

namespace {

using Crate = char;
using Stack = std::vector<Crate>;

using Amount = NamedType<std::size_t, struct AmountTag>;
using IndexFromStack = NamedType<std::size_t, struct IndexFromStackTag>;
using IndexToStack = NamedType<std::size_t, struct IndexToStackTag>;

class Move {
 public:
  static constexpr std::size_t inputIndexOffset{1};

  constexpr Move(Amount amount, IndexFromStack indexFromStack,
                 IndexToStack indexToStack)
      : _amount{amount.get()},
        _indexFromStack{indexFromStack.get() - inputIndexOffset},
        _indexToStack{indexToStack.get() - inputIndexOffset} {
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

using Stage = std::vector<Stack>;

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
    return fmt::format_to(ctx.out(), "{}", fmt::join(stage, ","sv));
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

constexpr auto countStacks(auto &&stackIdLine) -> std::size_t {
  return ranges::count_if(stackIdLine,
                          [](auto character) { return character != ' '; });
}

constexpr auto crateCharIndex(auto stackIndex) { return 1 + 4 * stackIndex; }

constexpr auto loadStage(auto &&linesView) -> Stage {
  auto lines = linesView | ranges::to<std::vector>();
  auto stackCount = countStacks(lines.back());
  SPDLOG_DEBUG("Stack count: {}", stackCount);

  auto crateLines =
      lines | views::reverse | views::drop(1) | ranges::to<std::vector>();

  return views::iota(std::size_t{}, stackCount) |
         views::transform(
             [](auto counter) { return crateCharIndex(counter); }) |
         views::transform([&crateLines](auto index) {
           return crateLines | views::transform([index](const auto &line) {
                    return *ranges::next(line.begin(), index);
                  }) |
                  views::take_while(
                      [](auto crateChar) { return crateChar != ' '; }) |
                  views::transform(
                      [](auto crateChar) { return Crate{crateChar}; });
         }) |
         ranges::to<Stage>();
}

constexpr auto parseMove(auto &&line) {
  auto parts = line | views::split(" "sv) | views::drop(1) | views::stride(2) |
               views::take(3) | views::transform([](auto &&value) {
                 return convert<std::size_t>(value);
               }) |
               ranges::to<std::vector>();
  return Move{Amount{parts.at(0)}, IndexFromStack{parts.at(1)},
              IndexToStack{parts.at(2)}};
}

constexpr auto loadMoves(auto &&lines) {
  return lines | views::transform([](auto &&line) {
           SPDLOG_DEBUG("DEBUG");
           SPDLOG_DEBUG("Parsing move: {}", line);
           return parseMove(line);
         });
}

constexpr auto loadParts(auto &&range) {
  auto parts =
      range | views::split("\n\n"sv) | views::transform([](auto part) {
        return part | views::split("\n"sv) |
               views::take_while([](auto line) { return !line.empty(); });
      }) |
      ranges::to<std::vector>();
  if (parts.size() != 2) {
    throw std::runtime_error("Incorrect parts");
  }

  return std::make_tuple(loadStage(parts.at(0) | views::all),
                         loadMoves(parts.at(1) | views::all));
}

[[nodiscard]] constexpr auto applySingleMove(auto prevStage, auto indexFrom,
                                             auto indexTo) -> Stage {
  auto &fromStack = prevStage.at(indexFrom);
  if (fromStack.empty()) {
    throw std::runtime_error("Moving from empty stack");
  }

  const Crate movedCrate{fromStack.back()};

#if 0  // #ifdef __cpp_lib_ranges_zip //NOLINT
#pragma message( \
    "Needs to be fixed. MSVC in Github supports this but debugging with it is difficult")
  return Stage{
      views::zip(views::iota(std::size_t{}), std::move(prevStage)) |
      views::transform([movedCrate, indexFrom, indexTo](auto enum_stack) {
        auto [i, stack] = std::move(enum_stack);
        if (i == indexFrom) {
          stack.pop_back();
        } else if (i == indexTo) {
          stack.emplace_back(movedCrate);
        }
        return stack;
      }) |
      ranges::to<Stage>()};
#else
  Stage stage;
  for (std::size_t index{}; auto &stack : prevStage) {
    if (index == indexFrom) {
      stack.pop_back();
    } else if (index == indexTo) {
      stack.emplace_back(movedCrate);
    }
    stage.emplace_back(std::move(stack));
    ++index;
  }
  return stage;
#endif
}

[[nodiscard]] constexpr auto applyMoveOneByOne(Stage stage,
                                               const Move &move) -> Stage {
  return ranges::fold_left(  // NOLINT(misc-include-cleaner)
      views::iota(std::size_t{}, move.amount()), std::move(stage),
      [&move](auto prev, auto) {
        auto stack = applySingleMove(std::move(prev), move.indexFromStack(),
                                     move.indexToStack());
        SPDLOG_DEBUG("Intermediate stage: {}", stack);
        return stack;
      });
}

auto solve1(auto input) {
  auto [stage, moves] = loadParts(input);
  SPDLOG_INFO("Initial stage: {}", stage);
  auto finalStage = ranges::fold_left(
      moves, std::move(stage), [](auto prev, const auto &move) {
        SPDLOG_DEBUG("Performing move ({}); Stage: {}", move, prev);
        auto next = applyMoveOneByOne(std::move(prev), move);
        SPDLOG_DEBUG("Move performed ({}); Stage: {}", move, next);
        return next;
      });

  return ranges::fold_left(
      finalStage, ""s,  // NOLINT(misc-include-cleaner)
      [](const auto &prev, const auto &stack) { return prev + stack.back(); });
}

}  // namespace

auto p1(std::string_view input) -> ResultType { return solve1(input); }

namespace {

[[nodiscard]] constexpr auto applyMoveInSingle(Stage prevStage,
                                               const Move &move) -> Stage {
  auto &movedFromStack = prevStage.at(move.indexFromStack());
  Stack movedCrates{};
  {
    auto movedIt = movedFromStack.begin();
    std::advance(movedIt, movedFromStack.size() - move.amount());
    std::move(movedIt, movedFromStack.end(), std::back_inserter(movedCrates));
    movedFromStack.erase(movedIt, movedFromStack.end());
  }

  Stage stage;
  for (std::size_t index{}; auto &stack : prevStage) {
    if (index == move.indexToStack()) {
      std::move(movedCrates.begin(), movedCrates.end(),
                std::back_inserter(stack));
    }
    stage.emplace_back(std::move(stack));
    ++index;
  }
  return stage;
}

constexpr auto solve2(auto input) {
  auto [stage, moves] = loadParts(input);
  SPDLOG_INFO("Initial stage: {}", stage);
  auto finalStage = ranges::fold_left(
      moves, std::move(stage), [](auto prev, const auto &move) {
        SPDLOG_DEBUG("Performing move ({}); Stage: {}", move, prev);
        auto next = applyMoveInSingle(std::move(prev), move);
        SPDLOG_DEBUG("Move performed ({}); Stage: {}", move, next);
        return next;
      });

  return ranges::fold_left(
      finalStage, ""s,
      [](const auto &prev, const auto &stack) { return prev + stack.back(); });
}

}  // namespace

auto p2(std::string_view input) -> ResultType { return solve2(input); }
