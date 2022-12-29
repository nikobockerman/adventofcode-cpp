#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <numeric>
#include <ranges>

#include "d1-common.hpp"
#include "program.hpp"
#include "utils.hpp"

namespace ranges = std::ranges;

namespace {

auto _main(auto input) {
  auto calorieSums = resolveCalorieSums(input) | toVector;
  spdlog::debug("Initial: {}", fmt::join(calorieSums, ","));

  constexpr std::size_t interestedSize{3};

  auto pastInteresting = ranges::next(calorieSums.begin(), interestedSize);
  ranges::nth_element(calorieSums, pastInteresting, std::greater<>());
  spdlog::debug("Partitioned: {}", fmt::join(calorieSums, ","));

  return std::accumulate(calorieSums.begin(), pastInteresting, 0);
}

}  // namespace

SHARED_MAIN
