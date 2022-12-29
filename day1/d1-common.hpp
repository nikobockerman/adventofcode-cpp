#pragma once

#include <numeric>
#include <ranges>
#include <string_view>

#include "convert.hpp"
#include "utils.hpp"

auto resolveCalorieSums(auto &&input) {
  constexpr std::string_view groupDelim{"\n\n"};

  return input | std::views::split(groupDelim) |
         std::views::transform([](auto calorieLines) {
           auto calorieValues = splitLinesUntilEmpty(calorieLines) |
                                std::views::transform([](auto calorieLine) {
                                  return convert<unsigned>(calorieLine);
                                }) |
                                std::views::common;
           return std::accumulate(calorieValues.begin(), calorieValues.end(),
                                  0U);
         });
}
