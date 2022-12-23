#include "day2-common.hpp"

#include "file-reader.hpp"

#include <charconv>
#include <fmt/ranges.h>
#include <numeric>
#include <spdlog/spdlog.h>

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
}

auto battleScore(Type opponent, Type me) -> unsigned {
  constexpr unsigned scoreLoss{0};
  constexpr unsigned scoreEven{3};
  constexpr unsigned scoreWin{6};

  if (opponent == me) {
    return scoreEven;
  }

  auto iWin = [=] {
    switch (opponent) {
    case Type::Paper:
      return me == Type::Scissors;
    case Type::Scissors:
      return me == Type::Rock;
    case Type::Rock:
      return me == Type::Paper;
    }
  };

  return iWin() ? scoreWin : scoreLoss;
}

class Battle {
public:
  Battle(Type opponent, Type me) : _opponent{opponent}, _me{me} {}

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

auto allBattles(auto &getNextLine, auto &parseMe) -> std::vector<Battle> {
  std::vector<Battle> battles;
  while (true) {
    auto line = getNextLine();
    if (!line.has_value()) {
      spdlog::debug("Received no line => EOF");
      break;
    }
    battles.emplace_back(getSingleBattle(line.value(), parseMe));
  }
  return battles;
}

} // namespace

auto sumScore(std::istream &input,
              const std::function<Type(Type, char)> &parseMe) -> unsigned {
  auto getNextLine = [&input]() { return ::readLine(input); };

  auto battles = allBattles(getNextLine, parseMe);
  std::vector<unsigned> scores;
  std::transform(battles.cbegin(), battles.cend(), std::back_inserter(scores),
                 [](auto &battle) { return battle.score(); });
  return std::accumulate(scores.begin(), scores.end(), 0U);
}
