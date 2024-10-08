#include <fmt/ranges.h>  // NOLINT(misc-include-cleaner) necessary include in debug builds
#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iterator>
#include <ranges>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "day-interface-y2022-d3.hpp"
#include "result-type.hpp"
#include "utils.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_view_literals;

namespace {

constexpr auto lowerCaseValue(char character) -> unsigned {
  return character - 'a';
}

constexpr auto isLowerCase(char character) {
  constexpr unsigned maxLowerCaseValue{'z' - 'a'};
  auto value = lowerCaseValue(character);
  return value <= maxLowerCaseValue;
}

constexpr auto lowerCasePriority(char character) {
  constexpr unsigned minPriority{1};
  constexpr unsigned maxPriority{26};

  auto result = lowerCaseValue(character) + minPriority;
  if (result < minPriority || result > maxPriority) {
    throw std::runtime_error("Invalid value");
  }
  return result;
}

constexpr auto upperCaseValue(char character) -> unsigned {
  return character - 'A';
}

constexpr auto isUpperCase(char character) {
  constexpr unsigned maxUpperCaseValue{'Z' - 'A'};
  auto value = upperCaseValue(character);
  return value <= maxUpperCaseValue;
}

constexpr auto upperCasePriority(char character) {
  constexpr unsigned minPriority{27};
  constexpr unsigned maxPriority{52};

  auto result = upperCaseValue(character) + minPriority;
  if (result < minPriority || result > maxPriority) {
    throw std::runtime_error("Invalid value");
  }
  return result;
}

constexpr auto priority(char sharedItem) -> unsigned {
  if (isLowerCase(sharedItem)) {
    return lowerCasePriority(sharedItem);
  }
  if (isUpperCase(sharedItem)) {
    return upperCasePriority(sharedItem);
  }
  throw std::runtime_error("Invalid character");
}

constexpr auto sumScore(auto &&items) -> uint64_t {
  auto result = ranges::fold_left_first(  // NOLINT(misc-include-cleaner)
      items |
          views::transform([](auto character) { return priority(character); }),
      std::plus());
  if (!result) {
    throw std::runtime_error("No result");
  }
  return result.value();
}

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

  SPDLOG_DEBUG("Intersection: {}", fmt::join(intersection, ","));
  if (intersection.size() != 1) {
    throw std::runtime_error("Unexpected number of intersections");
  }

  return intersection.at(0);
}

}  // namespace

auto y2022::d3::p1(std::string_view input) -> ResultType {
  return sumScore(
      splitLinesUntilEmpty(input) |
      views::transform([](auto &&line) { return getSharedItem(line); }));
}

namespace {

constexpr auto getGroupBadgeItem(auto &&groupRuckSacks) -> char {
  auto end = groupRuckSacks.end();
  auto iter = groupRuckSacks.begin();
  auto first = vectorSet(*iter);
  ranges::advance(iter, 1, end);
  auto second = vectorSet(*iter);
  ranges::advance(iter, 1, end);
  auto third = vectorSet(*iter);

  if (iter == end) {
    SPDLOG_DEBUG("Invalid group size: {}", ranges::distance(groupRuckSacks));
    throw std::runtime_error("Invalid group size");
  }

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
  SPDLOG_DEBUG("Group badge found: {}", badge);
  return badge;
}

constexpr auto solve2(auto input) {
  constexpr std::size_t groupSize{3};

  return sumScore(
      splitLinesUntilEmpty(input) | views::chunk(groupSize) |
      views::transform([](auto &&group) { return getGroupBadgeItem(group); }));
}

}  // namespace

auto y2022::d3::p2(std::string_view input) -> ResultType {
  return solve2(input);
}
