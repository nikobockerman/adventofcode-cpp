#include "day4-common.hpp"

#include "program.hpp"

#include <iostream>

namespace {

auto isContained(auto &containerSection, auto &checkedSection) {
  return static_cast<bool>(containerSection.start <= checkedSection.start &&
                           containerSection.end >= checkedSection.end);
}

auto areContained(auto &sectionPair) {
  return isContained(sectionPair.first, sectionPair.second) ||
         isContained(sectionPair.second, sectionPair.first);
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

  auto count = countSectionPairsIf(
      program->inputFile(), [](auto &pair) { return areContained(pair); });
  std::cout << "Result:" << std::endl << count << std::endl;

  return 0;
}
