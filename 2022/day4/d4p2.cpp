#include "common.hpp"
#include "d4-common.hpp"
#include "input.hpp"

namespace {

constexpr auto areSeparate(auto &sectionPair) {
  if (sectionPair.first.end < sectionPair.second.start) {
    return true;
  }
  if (sectionPair.second.end < sectionPair.first.start) {
    return true;
  }
  return false;
}

constexpr auto overlap(auto &sectionPair) { return !areSeparate(sectionPair); }

}  // namespace

auto main() -> int {
  enableDebugLogging();
  constexpr auto result =
      countSectionPairsIf(input, [](auto &pair) { return overlap(pair); });
  printResult(result);
  return 0;
}