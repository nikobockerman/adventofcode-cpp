#include <algorithm>
#include <numeric>
#include <ranges>
#include <string_view>

#include "common.hpp"
#include "input.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_view_literals;

using T2022_day1 = TestFixture;

namespace {

constexpr auto resolveCalorieSums(auto &&input) {
  return input | views::split("\n\n"sv) |
         views::transform([](auto calorieLines) {
           return ranges::fold_left_first(
                      splitLinesUntilEmpty(calorieLines) |
                          views::transform([](auto calorieLine) {
                            return convert<unsigned>(calorieLine);
                          }),
                      std::plus())
               .value();
         });
}

}  // namespace

TEST_F(T2022_day1, part1) {
  constexpr auto result = ranges::max(resolveCalorieSums(input));
  EXPECT_EQ(result, 69836);
}

namespace {

RUNTIME_CONSTEXPR auto solve2() {
  auto calorieSums = resolveCalorieSums(input) | ranges::to<std::vector>();
  logd("Initial: {}", fmt::join(calorieSums, ","));

  constexpr std::size_t interestedSize{3};

  auto pastInteresting = ranges::next(calorieSums.begin(), interestedSize);
  ranges::nth_element(calorieSums, pastInteresting, std::greater<>());
  logd("Partitioned: {}", fmt::join(calorieSums, ","));

  return ranges::fold_left_first(calorieSums.begin(), pastInteresting,
                                 std::plus())
      .value();
}

}  // namespace

TEST_F(T2022_day1, part2) {
  RUNTIME_CONSTEXPR auto result = solve2();
  EXPECT_EQ(result, 207968);
}
