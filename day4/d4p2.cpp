#include "d4-common.hpp"
#include "program.hpp"

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

constexpr auto _main(auto input) {
  return countSectionPairsIf(input, [](auto &pair) { return overlap(pair); });
}

}  // namespace

SHARED_MAIN
