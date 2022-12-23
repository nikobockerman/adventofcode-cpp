#include "day2-common.hpp"
#include "program.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>

namespace {

auto losingType(Type opponent) {
  switch (opponent) {
  case Type::Paper:
    return Type::Rock;
  case Type::Scissors:
    return Type::Paper;
  case Type::Rock:
    return Type::Scissors;
  }
}

auto winningType(Type opponent) {
  switch (opponent) {
  case Type::Paper:
    return Type::Scissors;
  case Type::Scissors:
    return Type::Rock;
  case Type::Rock:
    return Type::Paper;
  }
}

auto parseMe(Type opponent, char move) {
  switch (move) {
  case 'X':
    return losingType(opponent);
  case 'Y':
    return opponent;
  case 'Z':
    return winningType(opponent);
  }
  throw std::runtime_error("Unknown me type");
}

} // namespace

auto main(int argc, const char *const argv[]) -> int {
  auto [state, program] = Program::create("d2p2", {argc, argv});
  switch (state) {
  case State::Help:
    return 0;
  case State::Fail:
    return 1;
  case State::Ok:
    break;
  }

  auto sum = sumScore(program->inputFile(), parseMe);
  std::cout << "Result:" << std::endl << sum << std::endl;
  return 0;
}
