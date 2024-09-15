module;
#include <algorithm>
#include <ranges>
#include <string_view>
#include <vector>

#include "convert.hpp"
#include "utils.hpp"

export module y2022.d1;

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_view_literals;

// using T2022_day1 = TestFixture;

namespace {

auto resolveCalorieSums(std::string_view input) {
  return input | views::split("\n\n"sv) |
         views::transform([](auto calorieLines) {
           return ranges::fold_left_first(
                      splitLinesUntilEmpty(calorieLines) |
                          views::transform([](auto calorieLine) {
                            return convert<int>(calorieLine);
                          }),
                      std::plus())
               .value();
         });
}

}  // namespace

extern "C" auto p1(const char *input) -> int {
  auto result = ranges::max(resolveCalorieSums(input));
  // EXPECT_EQ(result, 69836);
  return result;
}

namespace {

// RUNTIME_CONSTEXPR auto solve2() {
auto solve2(std::string_view input) {
  auto calorieSums = resolveCalorieSums(input) | ranges::to<std::vector>();
  // logd("Initial: {}", fmt::join(calorieSums, ","));

  constexpr std::size_t interestedSize{3};

  auto pastInteresting = ranges::next(calorieSums.begin(), interestedSize);
  ranges::nth_element(calorieSums, pastInteresting, std::greater<>());
  // logd("Partitioned: {}", fmt::join(calorieSums, ","));

  return ranges::fold_left_first(calorieSums.begin(), pastInteresting,
                                 std::plus())
      .value();
}

}  // namespace

extern "C" auto p2(const char *input) -> int {
  // RUNTIME_CONSTEXPR auto result = solve2();
  auto result = solve2(input);
  // EXPECT_EQ(result, 207968);
  return result;
}
