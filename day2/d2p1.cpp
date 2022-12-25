#include <algorithm>
#include <iostream>
#include <numeric>

#include "day2-common.hpp"
#include "program.hpp"

namespace {

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

}  // namespace

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

  auto sum = sumScore(program->inputFile(),
                      [](auto, auto move) { return parseMe(move); });
  std::cout << "Result:" << std::endl << sum << std::endl;

  return 0;
}
