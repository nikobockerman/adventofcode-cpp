#include <fmt/ranges.h>  // NOLINT(misc-include-cleaner) necessary include in debug builds

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <ranges>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "convert.hpp"
#include "log.hpp"
#include "problem.hpp"
#include "utils.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_view_literals;

namespace {

constexpr auto resolveCalorieSums(auto &&input) {
  return input | views::split("\n\n"sv) |
         views::transform([](auto calorieLines) {
           return ranges::fold_left_first(  // NOLINT(misc-include-cleaner)
                      splitLinesUntilEmpty(calorieLines) |
                          views::transform([](auto calorieLine) {
                            return convert<int>(calorieLine);
                          }),
                      std::plus())
               .value();
         });
}

}  // namespace

auto p1(std::string_view input) -> ResultType {
  return ranges::max(resolveCalorieSums(input));
}

namespace {

auto solve2(std::string_view input) {
  auto calorieSums = resolveCalorieSums(input) | ranges::to<std::vector>();
  logd("Initial: {}", fmt::join(calorieSums, ","));

  constexpr std::size_t interestedSize{3};

  auto pastInteresting = ranges::next(calorieSums.begin(), interestedSize);
  ranges::nth_element(calorieSums, pastInteresting, std::greater<>());
  logd("Partitioned: {}", fmt::join(calorieSums, ","));

  auto result = ranges::fold_left_first(calorieSums.begin(), pastInteresting,
                                        std::plus());
  if (!result) {
    throw std::runtime_error("No result");
  }
  return result.value();
}

}  // namespace

auto p2(std::string_view input) -> ResultType { return solve2(input); }