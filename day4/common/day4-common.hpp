#pragma once

#include <functional>
#include <istream>
#include <utility>

class Section {
public:
  unsigned start;
  unsigned end;
};

auto countSectionPairsIf(
    std::istream &input,
    const std::function<bool(const std::pair<Section, Section> &)> &condition)
    -> unsigned;
