#include "common.hpp"
#include "d4-common.hpp"
#include "input.hpp"

namespace {

constexpr auto isContained(auto &containerSection, auto &checkedSection) {
  return static_cast<bool>(containerSection.start <= checkedSection.start &&
                           containerSection.end >= checkedSection.end);
}

constexpr auto areContained(auto &sectionPair) {
  return isContained(sectionPair.first, sectionPair.second) ||
         isContained(sectionPair.second, sectionPair.first);
}

}  // namespace

auto main() -> int {
  enableDebugLogging();
  RUNTIME_CONSTEXPR auto result =
      countSectionPairsIf(input, [](auto &pair) { return areContained(pair); });
  printResult(result);
  return 0;
}