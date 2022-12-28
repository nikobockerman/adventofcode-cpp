#include <spdlog/spdlog.h>

#include <algorithm>
#include <set>
#include <stdexcept>
#include <vector>

#include "day3-common.hpp"
#include "program.hpp"
#include "utils.hpp"

namespace {

auto items(auto ruckSack) {
  return std::set<char>{ruckSack.cbegin(), ruckSack.cend()};
}

auto getGroupBadgeItem(auto &groupRuckSacks) -> char {
  if (groupRuckSacks.size() != 3) {
    throw std::runtime_error("Invalid group size");
  }

  auto first = items(groupRuckSacks.at(0));
  auto second = items(groupRuckSacks.at(1));
  auto third = items(groupRuckSacks.at(2));

  std::set<char> firstIntersection;
  std::set_intersection(
      first.begin(), first.end(), second.begin(), second.end(),
      std::inserter(firstIntersection, std::end(firstIntersection)));

  std::set<char> intersection;
  std::set_intersection(firstIntersection.begin(), firstIntersection.end(),
                        third.begin(), third.end(),
                        std::inserter(intersection, std::end(intersection)));

  if (intersection.size() != 1) {
    throw std::runtime_error("Unexpected number of intersections");
  }

  auto badge = *intersection.begin();
  spdlog::debug("Group badge found: {}", badge);
  return badge;
}

auto _main(auto input) {
  auto lines = split(input, '\n');
  auto badgeItemGroups = group(lines, 3);

  std::vector<char> groupBadgeItems;
  std::transform(badgeItemGroups.begin(), badgeItemGroups.end(),
                 std::back_inserter(groupBadgeItems),
                 [](auto &group) { return getGroupBadgeItem(group); });

  return sumScore(groupBadgeItems);
}

}  // namespace

SHARED_MAIN
