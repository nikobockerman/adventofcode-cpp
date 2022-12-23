#include "day1-common.hpp"

#include "program.hpp"

#include <algorithm>
#include <fmt/format.h>
#include <iostream>
#include <numeric>
#include <spdlog/spdlog.h>
#include <stdexcept>

using namespace std::string_literals;

auto main(int argc, const char *const argv[]) -> int {
  auto [state, program] = Program::create("d1p2", {argc, argv});
  switch (state) {
  case State::Help:
    return 0;
  case State::Fail:
    return 1;
  case State::Ok:
    break;
  }

  auto calorieSums = resolveCalorieSums(program->inputFile());
  if (calorieSums.size() < 3) {
    throw std::runtime_error("Not enough data in input");
  }

  std::sort(calorieSums.begin(), calorieSums.end(), std::greater<>());
  spdlog::debug("Sorted: {}", fmt::join(calorieSums, ","));
  auto sum = std::accumulate(calorieSums.begin(), calorieSums.begin() + 3, 0);
  std::cout << "Result:" << std::endl << sum << std::endl;

  return 0;
}
