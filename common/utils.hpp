#pragma once

#include <algorithm>
#include <ranges>
#include <string_view>
#include <vector>

template <typename TValue, typename TDivider>
constexpr auto modulo(TValue value, TDivider divider) -> TValue {
  return value % divider;
}

constexpr auto splitLinesUntilEmpty(auto&& range) {
  constexpr std::string_view lineBreak{"\n"};
  return range | std::views::split(lineBreak) |
         std::views::take_while([](const auto& line) { return !line.empty(); });
}

constexpr auto vectorSet(auto&& range) {
  auto vector = range | std::ranges::to<std::vector>();
  std::ranges::sort(vector);
  auto ret = std::ranges::unique(vector);
  vector.erase(ret.begin(), ret.end());
  return vector;
}
