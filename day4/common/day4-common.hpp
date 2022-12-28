#pragma once

#include <functional>
#include <string_view>
#include <utility>

class Section {
 public:
  unsigned start;
  unsigned end;
};

auto countSectionPairsIf(
    std::string_view input,
    const std::function<bool(const std::pair<Section, Section> &)> &condition)
    -> unsigned;
