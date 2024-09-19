#include <numeric>
#include <ranges>
#include <stdexcept>

#include "common.hpp"
#include "input.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_view_literals;

using T2022_day2 = TestFixture;

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

constexpr auto battleScore(Type opponent, Type own) -> unsigned {
  constexpr unsigned scoreLoss{0};
  constexpr unsigned scoreEven{3};
  constexpr unsigned scoreWin{6};

  if (opponent == own) {
    return scoreEven;
  }

  auto iWin = [=] {
    switch (opponent) {
      case Type::Paper:
        return own == Type::Scissors;
      case Type::Scissors:
        return own == Type::Rock;
      case Type::Rock:
        return own == Type::Paper;
    }
    throw std::runtime_error("Unknown opponent type for win check");
  };

  return iWin() ? scoreWin : scoreLoss;
}

class Battle {
 public:
  constexpr Battle(Type opponent, Type own) : _opponent{opponent}, _me{own} {}

  [[nodiscard]] constexpr auto score() const -> unsigned {
    return typeScore(_me) + battleScore(_opponent, _me);
  }

 private:
  Type _opponent;
  Type _me;
};

constexpr auto parseOpponent(char move) {
  switch (move) {
    case 'A':
      return Type::Rock;
    case 'B':
      return Type::Paper;
    case 'C':
      return Type::Scissors;
  }
  throw std::runtime_error("Unknown opponent type");
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

constexpr auto sumBattleScores(auto &&range) -> unsigned {
  return ranges::fold_left_first(range | views::transform([](auto &&battle) {
                                   return battle.score();
                                 }),
                                 std::plus())
      .value();
}

}  // namespace

TEST_F(T2022_day2, part1) {
  auto parseMe = [](char move) constexpr {
    switch (move) {
      case 'X':
        return Type::Rock;
      case 'Y':
        return Type::Paper;
      case 'Z':
        return Type::Scissors;
    }
    throw std::runtime_error("Unknown me type");
  };
  constexpr auto result = sumBattleScores(
      getBattleMarks(input) | views::transform([&parseMe](auto marks) {
        return Battle(parseOpponent(marks.first), parseMe(marks.second));
      }));
  EXPECT_EQ(result, 8890);
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

TEST_F(T2022_day2, part2) {
  auto parseMe = [](Type opponent, char move) {
    switch (move) {
      case 'X':
        return losingType(opponent);
      case 'Y':
        return opponent;
      case 'Z':
        return winningType(opponent);
    }
    throw std::runtime_error("Unknown me type");
  };
  constexpr auto result = sumBattleScores(
      getBattleMarks(input) | views::transform([&parseMe](auto marks) {
        auto opponent = parseOpponent(marks.first);
        return Battle(opponent, parseMe(opponent, marks.second));
      }));
  EXPECT_EQ(result, 10238);
}
