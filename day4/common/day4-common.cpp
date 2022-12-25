#include "day4-common.hpp"

#include <spdlog/spdlog.h>

#include "convert.hpp"
#include "file-reader.hpp"

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
    std::istream &input,
    const std::function<bool(const std::pair<Section, Section> &)> &condition)
    -> unsigned {
  auto getNextLine = [&input]() { return ::readLine(input); };
  unsigned count{0};
  while (true) {
    auto line = getNextLine();
    if (!line.has_value()) {
      spdlog::debug("Received no line => EOF");
      break;
    }

    auto pair = getSectionPair(*line);
    if (condition(pair)) {
      ++count;
    }
  }
  return count;
}
