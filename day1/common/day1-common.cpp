#include "day1-common.hpp"

#include <algorithm>
#include <numeric>

#include "convert.hpp"
#include "utils.hpp"

auto resolveCalorieSums(std::string_view input) -> std::vector<unsigned> {
  auto lines = split(input, '\n');
  auto elfCalorieLines = split(lines, [](auto line) { return line.empty(); });

  auto sumCalorieLines = [](auto sum, auto calorieLine) constexpr {
    return sum + convert<unsigned>(calorieLine);
  };

  std::vector<unsigned> calorieSums;
  std::transform(elfCalorieLines.cbegin(), elfCalorieLines.cend(),
                 std::back_inserter(calorieSums),
                 [sumCalorieLines](auto &calories) {
                   return std::accumulate(calories.begin(), calories.end(), 0,
                                          sumCalorieLines);
                 });
  return calorieSums;
}
