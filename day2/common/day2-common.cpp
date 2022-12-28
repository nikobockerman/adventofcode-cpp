#include "day2-common.hpp"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <numeric>

#include "utils.hpp"

namespace {

auto typeScore(Type type) -> unsigned {
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

auto battleScore(Type opponent, Type own) -> unsigned {
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
  Battle(Type opponent, Type own) : _opponent{opponent}, _me{own} {}

  [[nodiscard]] auto score() const -> unsigned {
    return typeScore(_me) + battleScore(_opponent, _me);
  }

 private:
  Type _opponent;
  Type _me;
};

auto parseOpponent(char move) {
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

auto getSingleBattle(auto &line, auto &parseMe) {
  spdlog::debug("Parsing line: {}", line);
  if (line.length() != 3) {
    throw std::runtime_error("Unexpected line length");
  }
  if (line[1] != ' ') {
    throw std::runtime_error("Unexpedted char in line");
  }

  auto opponent{parseOpponent(line[0])};
  return Battle{opponent, parseMe(opponent, line[2])};
}

}  // namespace

auto sumScore(std::string_view input,
              const std::function<Type(Type, char)> &parseMe) -> unsigned {
  auto lines = split(input, '\n');
  std::vector<Battle> battles;
  std::transform(lines.begin(), lines.end(), std::back_inserter(battles),
                 [parseMe](auto &battleLine) {
                   return getSingleBattle(battleLine, parseMe);
                 });

  std::vector<unsigned> scores;
  std::transform(battles.cbegin(), battles.cend(), std::back_inserter(scores),
                 [](auto &battle) { return battle.score(); });
  return std::accumulate(scores.begin(), scores.end(), 0U);
}
