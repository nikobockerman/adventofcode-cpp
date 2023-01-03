#pragma once

#include <algorithm>
#include <functional>
#include <ranges>
#include <string_view>
#include <utility>

#include "convert.hpp"
#include "utils.hpp"

class Section {
 public:
  unsigned start;
  unsigned end;
};

namespace detail {

constexpr auto getSection(auto &&range) -> Section {
  constexpr std::string_view separator{"-"};
  auto sections = range | std::views::split(separator);
  return {convert<unsigned>(sections.front()),
          convert<unsigned>(*std::ranges::next(sections.begin(), 1))};
}

constexpr auto getSectionPair(auto &&line) {
  constexpr std::string_view separator{","};
  auto pairs = line | std::views::split(separator);
  return std::make_pair(getSection(pairs.front()),
                        getSection(*std::ranges::next(pairs.begin(), 1)));
}

}  // namespace detail

constexpr auto countSectionPairsIf(
    std::string_view input,
    const std::function<bool(const std::pair<Section, Section> &)> &condition) {
  auto pairs =
      splitLinesUntilEmpty(input) | std::views::transform([](auto &&line) {
        return detail::getSectionPair(line);
      });
  return std::ranges::count_if(
      pairs, [&condition](const auto &pair) { return condition(pair); });
}
