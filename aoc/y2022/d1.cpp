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

#include "convert.hpp"
#include "day-interface.hpp"
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
                            return convert<unsigned>(calorieLine);
                          }),
                      std::plus())
               .value();
         });
}

}  // namespace

auto p1(std::string_view input) -> ResultType {
  return static_cast<uint64_t>(ranges::max(resolveCalorieSums(input)));
}

namespace {

auto solve2(std::string_view input) -> uint64_t {
  auto calorieSums = resolveCalorieSums(input) | ranges::to<std::vector>();
  SPDLOG_DEBUG("Initial: {}", fmt::join(calorieSums, ","));

  constexpr std::size_t interestedSize{3};

  auto pastInteresting = ranges::next(calorieSums.begin(), interestedSize);
  ranges::nth_element(calorieSums, pastInteresting, std::greater<>());
  SPDLOG_DEBUG("Partitioned: {}", fmt::join(calorieSums, ","));

  auto result = ranges::fold_left_first(calorieSums.begin(), pastInteresting,
                                        std::plus());
  if (!result) {
    throw std::runtime_error("No result");
  }
  return result.value();
}

}  // namespace

auto p2(std::string_view input) -> ResultType { return solve2(input); }
