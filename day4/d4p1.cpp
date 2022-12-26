#include "day4-common.hpp"
#include "program.hpp"

namespace {

auto isContained(auto &containerSection, auto &checkedSection) {
  return static_cast<bool>(containerSection.start <= checkedSection.start &&
                           containerSection.end >= checkedSection.end);
}

auto areContained(auto &sectionPair) {
  return isContained(sectionPair.first, sectionPair.second) ||
         isContained(sectionPair.second, sectionPair.first);
}

auto _main(auto input) {
  return countSectionPairsIf(input,
                             [](auto &pair) { return areContained(pair); });
}

}  // namespace

SHARED_MAIN
