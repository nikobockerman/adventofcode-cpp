#include <algorithm>
#include <numeric>
#include <ranges>

#include "common.hpp"
#include "d1-common.hpp"
#include "input.hpp"

namespace ranges = std::ranges;

namespace {

RUNTIME_CONSTEXPR auto solve() {
  auto calorieSums = resolveCalorieSums(input) | ranges::to<std::vector>();
  logd("Initial: {}", fmt::join(calorieSums, ","));

  constexpr std::size_t interestedSize{3};

  auto pastInteresting = ranges::next(calorieSums.begin(), interestedSize);
  ranges::nth_element(calorieSums, pastInteresting, std::greater<>());
  logd("Partitioned: {}", fmt::join(calorieSums, ","));

  return std::accumulate(calorieSums.begin(), pastInteresting, 0);
}

}  // namespace

auto main() -> int {
  enableDebugLogging();
  RUNTIME_CONSTEXPR auto result = solve();
  printResult(result);
  return 0;
}
