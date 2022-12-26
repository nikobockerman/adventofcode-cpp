#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <numeric>
#include <stdexcept>

#include "day1-common.hpp"
#include "program.hpp"

using namespace std::string_literals;

namespace {

auto _main(auto input) {
  auto calorieSums = resolveCalorieSums(input);
  if (calorieSums.size() < 3) {
    throw std::runtime_error("Not enough data in input");
  }

  std::sort(calorieSums.begin(), calorieSums.end(), std::greater<>());
  spdlog::debug("Sorted: {}", fmt::join(calorieSums, ","));
  return std::accumulate(calorieSums.begin(), calorieSums.begin() + 3, 0);
}

}  // namespace

SHARED_MAIN
