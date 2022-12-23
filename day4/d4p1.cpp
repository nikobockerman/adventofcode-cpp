#include "convert.hpp"
#include "file-reader.hpp"
#include "program.hpp"

#include <iostream>
#include <optional>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace {

auto getSharedItem(auto &rucksack) {
  if (rucksack.empty()) {
    throw std::runtime_error("Empty rucksack");
  }

  auto [first, second] = getCompartments(rucksack);
  std::set<char> firstItems{first.cbegin(), first.cend()};
  std::set<char> secondItems{second.cbegin(), second.cend()};

  std::vector<char> intersection;
  std::set_intersection(firstItems.begin(), firstItems.end(),
                        secondItems.begin(), secondItems.end(),
                        std::back_inserter(intersection));

  if (intersection.size() != 1) {
    throw std::runtime_error("Unexpected number of intersections");
  }

  return intersection.at(0);
}

class Section {
public:
  unsigned start;
  unsigned end;
};

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

auto isContained(auto &containerSection, auto &checkedSection) {
  return static_cast<bool>(containerSection.start <= checkedSection.start &&
                           containerSection.end >= checkedSection.end);
}

auto areContained(auto &sectionPair) {
  return isContained(sectionPair.first, sectionPair.second) ||
         isContained(sectionPair.second, sectionPair.first);
}

auto countOfContainedSectionPairs(auto &getNextLine) {
  unsigned count{0};
  while (true) {
    auto line = getNextLine();
    if (!line.has_value()) {
      spdlog::debug("Received no line => EOF");
      break;
    }

    auto pair = getSectionPair(*line);
    if (areContained(pair)) {
      ++count;
    }
  }
  return count;
}

} // namespace

auto main(int argc, const char *const argv[]) -> int {
  auto [state, program] = Program::create("d4p1", {argc, argv});
  switch (state) {
  case State::Help:
    return 0;
  case State::Fail:
    return 1;
  case State::Ok:
    break;
  }

  auto getNextLine = [&input = program->inputFile()]() {
    return ::readLine(input);
  };

  auto count = countOfContainedSectionPairs(getNextLine);
  std::cout << "Result:" << std::endl << count << std::endl;

  return 0;
}
