#include <cstdint>
#include <functional>
#include <iterator>
#include <ranges>
#include <stdexcept>
#include <string_view>

#include "day-interface-y2022-d2.hpp"
#include "named-type.hpp"
#include "result-type.hpp"
#include "utils.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_view_literals;

namespace {

enum class Type : std::uint8_t { Rock, Paper, Scissors };

constexpr auto typeScore(Type type) -> unsigned {
  switch (type) {
    case Type::Rock:
      return 1;
    case Type::Paper:
      return 2;
    case Type::Scissors:
      return 3;
  }
  throw std::runtime_error("Unknown type for score");
}

using OpponentType = NamedType<Type, struct OpponentTypeTag>;
using OwnType = NamedType<Type, struct OwnTypeTag>;

constexpr auto battleScore(OpponentType opponent, OwnType own) -> unsigned {
  constexpr unsigned scoreLoss{0};
  constexpr unsigned scoreEven{3};
  constexpr unsigned scoreWin{6};

  if (opponent.get() == own.get()) {
    return scoreEven;
  }

  auto iWin = [=] {
    switch (opponent.get()) {
      case Type::Paper:
        return own.get() == Type::Scissors;
      case Type::Scissors:
        return own.get() == Type::Rock;
      case Type::Rock:
        return own.get() == Type::Paper;
    }
    throw std::runtime_error("Unknown opponent type for win check");
  };

  return iWin() ? scoreWin : scoreLoss;
}

class Battle {
 public:
  constexpr Battle(OpponentType opponent, OwnType own)
      : _opponent{opponent}, _me{own} {}

  [[nodiscard]] constexpr auto score() const -> unsigned {
    return typeScore(_me.get()) + battleScore(_opponent, _me);
  }

 private:
  OpponentType _opponent;
  OwnType _me;
};

constexpr auto parseOpponent(char move) {
  switch (move) {
    case 'A':
      return OpponentType{Type::Rock};
    case 'B':
      return OpponentType{Type::Paper};
    case 'C':
      return OpponentType{Type::Scissors};
    default:
      throw std::runtime_error("Unknown opponent type");
  }
}

constexpr auto parseBattleMarks(auto &&line) {
  auto end = line.end();
  auto iter = line.begin();
  auto opponentMark = *iter;
  ranges::advance(iter, 2, end);
  auto meMark = *iter;
  if (iter == end) {
    throw std::runtime_error("Unpexpected line");
  }
  return std::make_pair(opponentMark, meMark);
}

constexpr auto getBattleMarks(auto &&range) {
  return splitLinesUntilEmpty(range) |
         views::transform([](auto &&line) { return parseBattleMarks(line); });
}

constexpr auto sumBattleScores(auto &&range) -> uint64_t {
  auto result = ranges::fold_left_first(  // NOLINT(misc-include-cleaner)
      range | views::transform([](auto &&battle) { return battle.score(); }),
      std::plus());
  if (!result) {
    throw std::runtime_error("No result");
  }
  return result.value();
}

}  // namespace

auto y2022::d2::p1(std::string_view input) -> ResultType {
  auto parseMe = [](char move) constexpr {
    switch (move) {
      case 'X':
        return OwnType{Type::Rock};
      case 'Y':
        return OwnType{Type::Paper};
      case 'Z':
        return OwnType{Type::Scissors};
      default:
        throw std::runtime_error("Unknown me type");
    }
  };
  return sumBattleScores(
      getBattleMarks(input) | views::transform([&parseMe](auto marks) {
        return Battle{parseOpponent(marks.first), parseMe(marks.second)};
      }));
}

namespace {

constexpr auto losingType(Type opponent) {
  switch (opponent) {
    case Type::Paper:
      return Type::Rock;
    case Type::Scissors:
      return Type::Paper;
    case Type::Rock:
      return Type::Scissors;
  }
  throw std::runtime_error("Unknown opponent type for losing");
}

constexpr auto winningType(Type opponent) {
  switch (opponent) {
    case Type::Paper:
      return Type::Scissors;
    case Type::Scissors:
      return Type::Rock;
    case Type::Rock:
      return Type::Paper;
  }
  throw std::runtime_error("Unknown opponent type for winning");
}

}  // namespace

auto y2022::d2::p2(std::string_view input) -> ResultType {
  auto parseMe = [](OpponentType opponent, char move) {
    switch (move) {
      case 'X':
        return OwnType{losingType(opponent.get())};
      case 'Y':
        return OwnType{opponent.get()};
      case 'Z':
        return OwnType{winningType(opponent.get())};
      default:
        throw std::runtime_error("Unknown me type");
    }
  };
  return sumBattleScores(
      getBattleMarks(input) | views::transform([&parseMe](auto marks) {
        auto opponent = parseOpponent(marks.first);
        return Battle{opponent, parseMe(opponent, marks.second)};
      }));
}
