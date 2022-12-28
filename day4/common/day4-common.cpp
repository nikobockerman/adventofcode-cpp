#include "day4-common.hpp"

#include <spdlog/spdlog.h>

#include "convert.hpp"
#include "utils.hpp"

namespace {

auto getSection(std::string_view range) -> Section {
  auto rangeSeparator = range.find('-');
  if (rangeSeparator == std::string_view::npos) {
    throw std::runtime_error("No range separator");
  }

  return {convert<unsigned>(range.substr(0, rangeSeparator)),
          convert<unsigned>(range.substr(rangeSeparator + 1))};
}

auto getSectionPair(std::string_view line) -> std::pair<Section, Section> {
  auto pairSeparator = line.find(',');
  if (pairSeparator == std::string_view::npos) {
    throw std::runtime_error("No pair separator comma");
  }

  return {getSection(line.substr(0, pairSeparator)),
          getSection(line.substr(pairSeparator + 1))};
}

}  // namespace

auto countSectionPairsIf(
    std::string_view input,
    const std::function<bool(const std::pair<Section, Section> &)> &condition)
    -> unsigned {
  auto lines = split(input, '\n');
  return std::count_if(lines.begin(), lines.end(), [condition](auto line) {
    auto pair = getSectionPair(line);
    return condition(pair);
  });
}
