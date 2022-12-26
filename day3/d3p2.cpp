#include <spdlog/spdlog.h>

#include <algorithm>
#include <set>
#include <stdexcept>
#include <vector>

#include "day3-common.hpp"
#include "file-reader.hpp"
#include "program.hpp"

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

auto getGroupRuckSacks(auto &getNextLine) {
  std::vector<std::string> groupRuckSacks;
  while (true) {
    auto line = getNextLine();
    if (!line.has_value()) {
      spdlog::debug("Received no line => EOF");
      break;
    }

    groupRuckSacks.emplace_back(std::move(line.value()));
    if (groupRuckSacks.size() >= 3) {
      spdlog::debug("Received 3 ruck sacks");
      break;
    }
  }
  return groupRuckSacks;
}

auto getGroupBadgeItems(auto &getNextLine) {
  std::vector<char> badgeItems;
  while (true) {
    auto groupRuckSacks = getGroupRuckSacks(getNextLine);
    if (groupRuckSacks.empty()) {
      spdlog::debug("No rucksacks => EOF");
      break;
    }

    badgeItems.emplace_back(getGroupBadgeItem(groupRuckSacks));
  }
  return badgeItems;
}

auto _main(auto input) {
  auto getNextLine = [&input]() { return ::readLine(input); };
  auto groupBadgeItems = getGroupBadgeItems(getNextLine);

  return sumScore(groupBadgeItems);
}

}  // namespace

SHARED_MAIN
