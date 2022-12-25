#include <spdlog/spdlog.h>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <stdexcept>
#include <string_view>
#include <utility>

#include "day3-common.hpp"
#include "file-reader.hpp"
#include "program.hpp"

namespace {

auto modulo(auto value, auto divider) { return value % divider; }

auto middle(auto rucksack) {
  if (modulo(rucksack.length(), 2) != 0) {
    throw std::runtime_error("Uneven length");
  }
  return rucksack.length() / 2;
}

auto getCompartments(std::string_view rucksack)
    -> std::pair<std::string_view, std::string_view> {
  const auto mid = middle(rucksack);

  return {rucksack.substr(0, mid), rucksack.substr(mid)};
}

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

auto getAllSharedItems(auto &getNextLine) {
  std::vector<char> sharedItems;
  while (true) {
    auto line = getNextLine();
    if (!line.has_value()) {
      spdlog::debug("Received no line => EOF");
      break;
    }
    sharedItems.emplace_back(getSharedItem(*line));
  }
  return sharedItems;
}

}  // namespace

auto main(int argc, const char *const argv[]) -> int {
  auto [state, program] = Program::create("d3p1", {argc, argv});
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
  auto sharedItems = getAllSharedItems(getNextLine);

  auto sum = sumScore(sharedItems);
  std::cout << "Result:" << std::endl << sum << std::endl;

  return 0;
}
