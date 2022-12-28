#include <spdlog/spdlog.h>

#include <algorithm>
#include <set>
#include <stdexcept>
#include <vector>

#include "day3-common.hpp"
#include "program.hpp"
#include "utils.hpp"

namespace {

auto middle(auto rucksack) {
  if (modulo(rucksack.length(), 2) != 0) {
    throw std::runtime_error("Uneven length");
  }
  return rucksack.length() / 2;
}

auto getCompartments(std::string_view rucksack)
    -> std::pair<std::string_view, std::string_view> {
  const auto mid = middle(rucksack);

  return {rucksack.substr(0, mid), rucksack.substr(mid)};
}

auto getSharedItem(auto &rucksack) {
  if (rucksack.empty()) {
    throw std::runtime_error("Empty rucksack");
  }

  auto [first, second] = getCompartments(rucksack);
  std::set<char> firstItems{first.cbegin(), first.cend()};
  std::set<char> secondItems{second.cbegin(), second.cend()};

  std::vector<char> intersection;
  std::set_intersection(firstItems.begin(), firstItems.end(),
                        secondItems.begin(), secondItems.end(),
                        std::back_inserter(intersection));

  if (intersection.size() != 1) {
    throw std::runtime_error("Unexpected number of intersections");
  }

  return intersection.at(0);
}

auto _main(auto input) {
  auto lines = split(input, '\n');
  std::vector<char> sharedItems;
  std::transform(lines.begin(), lines.end(), std::back_inserter(sharedItems),
                 [](auto line) { return getSharedItem(line); });

  return sumScore(sharedItems);
}

}  // namespace

SHARED_MAIN
