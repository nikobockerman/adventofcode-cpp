#include <iostream>

#include "day4-common.hpp"
#include "program.hpp"

namespace {

auto areSeparate(auto &sectionPair) {
  if (sectionPair.first.end < sectionPair.second.start) {
    return true;
  }
  if (sectionPair.second.end < sectionPair.first.start) {
    return true;
  }
  return false;
}

auto overlap(auto &sectionPair) { return !areSeparate(sectionPair); }

}  // namespace

auto main(int argc, const char *const argv[]) -> int {
  auto [state, program] = Program::create("d4p2", {argc, argv});
  switch (state) {
    case State::Help:
      return 0;
    case State::Fail:
      return 1;
    case State::Ok:
      break;
  }

  auto count = countSectionPairsIf(program->inputFile(),
                                   [](auto &pair) { return overlap(pair); });
  std::cout << "Result:" << std::endl << count << std::endl;

  return 0;
}
