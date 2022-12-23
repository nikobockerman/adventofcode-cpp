#include "file-reader.hpp"
#include "program.hpp"

#include <iostream>
#include <iterator>
#include <numeric>
#include <spdlog/spdlog.h>
#include <stdexcept>

namespace {

enum class Type { Rock, Paper, Scissors };

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

  [[nodiscard]] auto score() const {
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

auto parseMe(char move) {
  switch (move) {
  case 'X':
    return Type::Rock;
  case 'Y':
    return Type::Paper;
  case 'Z':
    return Type::Scissors;
  }
  throw std::runtime_error("Unknown me type");
}

auto getSingleBattle(auto &line) {
  spdlog::debug("Parsing line: {}", line);
  if (line.length() != 3) {
    throw std::runtime_error("Unexpected line length");
  }
  if (line[1] != ' ') {
    throw std::runtime_error("Unexpedted char in line");
  }

  return Battle{parseOpponent(line[0]), parseMe(line[2])};
}

auto allBattles(auto &getNextLine) {
  std::vector<Battle> battles;
  while (true) {
    auto line = getNextLine();
    if (!line.has_value()) {
      spdlog::debug("Received no line => EOF");
      break;
    }
    battles.emplace_back(getSingleBattle(line.value()));
  }
  return battles;
}

} // namespace

auto main(int argc, const char *const argv[]) -> int {
  auto [state, program] = Program::create("d2p1", {argc, argv});
  switch (state) {
  case State::Help:
    return 0;
  case State::Fail:
    return 1;
  case State::Ok:
    break;
  }

  auto getNextLine = [&input = program->inputFile()]() {
    return ::readLine(input);
  };
  auto battles = allBattles(getNextLine);

  std::vector<unsigned> scores;
  std::transform(battles.cbegin(), battles.cend(), std::back_inserter(scores),
                 [](auto &battle) { return battle.score(); });
  auto sum = std::accumulate(scores.begin(), scores.end(), 0U);

  std::cout << "Result:" << std::endl << sum << std::endl;

  return 0;
}
