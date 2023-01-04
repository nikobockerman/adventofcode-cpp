#include <algorithm>
#include <ranges>
#include <set>
#include <stdexcept>
#include <vector>

#include "common.hpp"
#include "d3-common.hpp"
#include "input.hpp"

using namespace std::string_view_literals;

namespace ranges = std::ranges;
namespace views = std::views;

namespace {

RUNTIME_CONSTEXPR auto getGroupBadgeItem(auto &&groupRuckSacks) -> char {
  auto size = ranges::distance(groupRuckSacks);
  if (size != 3) {
    logd("Invalid group size: {}", size);
    throw std::runtime_error("Invalid group size");
  }

  auto first = vectorSet(*groupRuckSacks.begin());
  auto second = vectorSet(*ranges::next(groupRuckSacks.begin(), 1));
  auto third = vectorSet(*ranges::next(groupRuckSacks.begin(), 2));

  std::vector<char> firstIntersection;
  ranges::set_intersection(first, second,
                           std::back_inserter(firstIntersection));

  std::vector<char> intersection;
  ranges::set_intersection(firstIntersection, third,
                           std::back_inserter(intersection));

  if (intersection.size() != 1) {
    throw std::runtime_error("Unexpected number of intersections");
  }

  auto badge = intersection.at(0);
  logd("Group badge found: {}", badge);
  return badge;
}

constexpr auto solve() {
  constexpr std::size_t groupSize{3};

  return sumScore(
      splitLinesUntilEmpty(input) | views::chunk(groupSize) |
      views::transform([](auto &&group) { return getGroupBadgeItem(group); }));
}

}  // namespace

auto main() -> int {
  enableDebugLogging();
  RUNTIME_CONSTEXPR auto result = solve();
  printResult(result);
  return 0;
}