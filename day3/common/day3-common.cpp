#include "day3-common.hpp"

#include <numeric>
#include <stdexcept>

namespace {

auto lowerCaseValue(char c) -> unsigned { return c - 'a'; }

auto isLowerCase(char c) {
  constexpr unsigned maxLowerCaseValue{'z' - 'a'};
  auto value = lowerCaseValue(c);
  return value <= maxLowerCaseValue;
}

auto lowerCasePriority(char c) {
  constexpr unsigned minPriority{1};
  constexpr unsigned maxPriority{26};

  auto result = lowerCaseValue(c) + minPriority;
  if (result < minPriority || result > maxPriority) {
    throw std::runtime_error("Invalid value");
  }
  return result;
}

auto upperCaseValue(char c) -> unsigned { return c - 'A'; }

auto isUpperCase(char c) {
  constexpr unsigned maxUpperCaseValue{'Z' - 'A'};
  auto value = upperCaseValue(c);
  return value <= maxUpperCaseValue;
}

auto upperCasePriority(char c) {
  constexpr unsigned minPriority{27};
  constexpr unsigned maxPriority{52};

  auto result = upperCaseValue(c) + minPriority;
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

} // namespace

auto sumScore(const std::vector<char> &items) -> unsigned {
  std::vector<unsigned> priorities;
  std::transform(items.cbegin(), items.cend(), std::back_inserter(priorities),
                 [](char c) { return priority(c); });
  return std::accumulate(priorities.cbegin(), priorities.cend(), 0);
}
