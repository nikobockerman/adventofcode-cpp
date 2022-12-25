#include <algorithm>
#include <iostream>

#include "day1-common.hpp"
#include "program.hpp"

using namespace std::string_literals;

auto main(int argc, const char *const argv[]) -> int {
  auto [state, program] = Program::create("d1p1", {argc, argv});
  switch (state) {
    case State::Help:
      return 0;
    case State::Fail:
      return 1;
    case State::Ok:
      break;
  }

  auto calorieSums = resolveCalorieSums(program->inputFile());

  auto result = std::max_element(calorieSums.cbegin(), calorieSums.cend());
  std::cout << "Result:" << std::endl << *result << std::endl;

  return 0;
}
