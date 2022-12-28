#include "day3-common.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace {

auto lowerCaseValue(char character) -> unsigned { return character - 'a'; }

auto isLowerCase(char character) {
  constexpr unsigned maxLowerCaseValue{'z' - 'a'};
  auto value = lowerCaseValue(character);
  return value <= maxLowerCaseValue;
}

auto lowerCasePriority(char character) {
  constexpr unsigned minPriority{1};
  constexpr unsigned maxPriority{26};

  auto result = lowerCaseValue(character) + minPriority;
  if (result < minPriority || result > maxPriority) {
    throw std::runtime_error("Invalid value");
  }
  return result;
}

auto upperCaseValue(char character) -> unsigned { return character - 'A'; }

auto isUpperCase(char character) {
  constexpr unsigned maxUpperCaseValue{'Z' - 'A'};
  auto value = upperCaseValue(character);
  return value <= maxUpperCaseValue;
}

auto upperCasePriority(char character) {
  constexpr unsigned minPriority{27};
  constexpr unsigned maxPriority{52};

  auto result = upperCaseValue(character) + minPriority;
  if (result < minPriority || result > maxPriority) {
    throw std::runtime_error("Invalid value");
  }
  return result;
}

auto priority(char sharedItem) -> unsigned {
  if (isLowerCase(sharedItem)) {
    return lowerCasePriority(sharedItem);
  }
  if (isUpperCase(sharedItem)) {
    return upperCasePriority(sharedItem);
  }
  throw std::runtime_error("Invalid character");
}

}  // namespace

auto sumScore(const std::vector<char> &items) -> unsigned {
  std::vector<unsigned> priorities;
  std::transform(items.cbegin(), items.cend(), std::back_inserter(priorities),
                 [](char character) { return priority(character); });
  return std::accumulate(priorities.cbegin(), priorities.cend(), 0);
}
