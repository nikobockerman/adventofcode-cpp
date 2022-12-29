#include <spdlog/spdlog.h>

#include <algorithm>
#include <ranges>
#include <set>
#include <stdexcept>
#include <vector>

#include "d3-common.hpp"
#include "program.hpp"
#include "utils.hpp"

using namespace std::string_view_literals;

namespace ranges = std::ranges;
namespace views = std::views;

namespace {

constexpr auto getGroupBadgeItem(auto &&groupRuckSacks) -> char {
  if (groupRuckSacks.size() != 3) {
    spdlog::debug("Invalid group size: {}", groupRuckSacks.size());
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
  spdlog::debug("Group badge found: {}", badge);
  return badge;
}

constexpr auto _main(auto input) {
  constexpr std::size_t groupSize{3};

  return sumScore(
      splitLinesUntilEmpty(input) | customChunkView(groupSize) |
      views::transform([](auto &&group) { return getGroupBadgeItem(group); }));
}

}  // namespace

SHARED_MAIN
