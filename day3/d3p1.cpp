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

constexpr auto middle(const auto &rucksack) {
  if (modulo(rucksack.size(), 2) != 0) {
    throw std::runtime_error("Uneven length");
  }
  return rucksack.size() / 2;
}

constexpr auto getCompartments(const auto &rucksack) {
  const auto mid = middle(rucksack);

  return std::make_pair(rucksack | views::take(mid),
                        rucksack | views::drop(mid));
}

constexpr auto getSharedItem(auto &&rucksack) {
  if (rucksack.empty()) {
    throw std::runtime_error("Empty rucksack");
  }

  auto [firstItems, secondItems] = getCompartments(rucksack);
  auto first = vectorSet(std::move(firstItems));
  auto second = vectorSet(std::move(secondItems));

  auto intersection = std::vector<char>{};
  ranges::set_intersection(first, second, std::back_inserter(intersection));

  spdlog::debug("Intersection: {}", fmt::join(intersection, ","));
  if (intersection.size() != 1) {
    throw std::runtime_error("Unexpected number of intersections");
  }

  return intersection.at(0);
}

constexpr auto _main(auto input) {
  return sumScore(
      splitLinesUntilEmpty(input) |
      views::transform([](auto &&line) { return getSharedItem(line); }));
}

}  // namespace

SHARED_MAIN
