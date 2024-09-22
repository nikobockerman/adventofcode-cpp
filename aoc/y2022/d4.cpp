#include <gtest/gtest.h>

#include <algorithm>
#include <ranges>
#include <vector>

#include "convert.hpp"
#include "input.hpp"
#include "test.hpp"
#include "utils.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_view_literals;

using T2022Day4 = TestFixture;

namespace {

class Section {
 public:
  unsigned start;
  unsigned end;
};

constexpr auto getSection(auto &&range) -> Section {
  auto values = range | views::split('-') | ranges::to<std::vector>();
  return {convert<unsigned>(values.at(0)), convert<unsigned>(values.at(1))};
}

constexpr auto getSectionPair(auto &&line) {
  auto pairs = line | views::split(',') | ranges::to<std::vector>();
  return std::make_pair(getSection(pairs.at(0)), getSection(pairs.at(1)));
}

constexpr auto getSectionPairs(auto &&range) {
  return splitLinesUntilEmpty(range) |
         views::transform([](auto &&line) { return getSectionPair(line); });
}

constexpr auto isContained(auto &containerSection, auto &checkedSection) {
  return containerSection.start <= checkedSection.start &&
         containerSection.end >= checkedSection.end;
}

constexpr auto areContained(auto &sectionPair) {
  return isContained(sectionPair.first, sectionPair.second) ||
         isContained(sectionPair.second, sectionPair.first);
}

constexpr auto solve1() {
  auto pairs = getSectionPairs(input);
  return ranges::count_if(pairs,
                          [](const auto &pair) { return areContained(pair); });
}

}  // namespace

TEST_F(T2022Day4, part1) {
  constexpr auto result = solve1();
  EXPECT_EQ(result, 536);
}

namespace {

constexpr auto areSeparate(auto &sectionPair) {
  return sectionPair.first.end < sectionPair.second.start ||
         sectionPair.second.end < sectionPair.first.start;
}

constexpr auto overlap(auto &sectionPair) { return !areSeparate(sectionPair); }

constexpr auto solve2() {
  auto pairs = getSectionPairs(input);
  return ranges::count_if(pairs,
                          [](const auto &pair) { return overlap(pair); });
}

}  // namespace

TEST_F(T2022Day4, part2) {
  constexpr auto result = solve2();
  EXPECT_EQ(result, 845);
}
