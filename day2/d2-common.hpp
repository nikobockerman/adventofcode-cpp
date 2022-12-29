#pragma once

#include <functional>
#include <numeric>
#include <stdexcept>
#include <string_view>

#include "utils.hpp"

enum class Type { Rock, Paper, Scissors };

namespace detail {

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

constexpr auto getSingleBattle(const auto &line, auto &parseMe) {
  if (line.size() != 3) {
    throw std::runtime_error("Unexpected line length");
  }
  if (line[1] != ' ') {
    throw std::runtime_error("Unexpedted char in line");
  }

  auto opponent{parseOpponent(line[0])};
  return Battle{opponent, parseMe(opponent, line[2])};
}

}  // namespace detail

constexpr auto sumScore(std::string_view input,
                        const std::function<Type(Type, char)> &parseMe)
    -> unsigned {
  auto scores =
      splitLinesUntilEmpty(input) |
      std::views::transform([&parseMe](auto &&line) {
        return detail::getSingleBattle(line, parseMe);
      }) |
      std::views::transform([](auto &&battle) { return battle.score(); }) |
      std::views::common;

  return std::accumulate(scores.begin(), scores.end(), 0U);
}
