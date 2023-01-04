#include <algorithm>
#include <ranges>

#include "common.hpp"
#include "d1-common.hpp"
#include "input.hpp"

auto main() -> int {
  enableDebugLogging();
  constexpr auto result = std::ranges::max(resolveCalorieSums(input));
  printResult(result);
  return 0;
}
