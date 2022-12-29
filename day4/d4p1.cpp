#include "d4-common.hpp"
#include "program.hpp"

namespace {

constexpr auto isContained(auto &containerSection, auto &checkedSection) {
  return static_cast<bool>(containerSection.start <= checkedSection.start &&
                           containerSection.end >= checkedSection.end);
}

constexpr auto areContained(auto &sectionPair) {
  return isContained(sectionPair.first, sectionPair.second) ||
         isContained(sectionPair.second, sectionPair.first);
}

constexpr auto _main(auto input) {
  return countSectionPairsIf(input,
                             [](auto &pair) { return areContained(pair); });
}

}  // namespace

SHARED_MAIN
