#pragma once

#include <numeric>
#include <ranges>
#include <stdexcept>
#include <vector>

namespace detail {

constexpr auto lowerCaseValue(char character) -> unsigned {
  return character - 'a';
}

constexpr auto isLowerCase(char character) {
  constexpr unsigned maxLowerCaseValue{'z' - 'a'};
  auto value = lowerCaseValue(character);
  return value <= maxLowerCaseValue;
}

constexpr auto lowerCasePriority(char character) {
  constexpr unsigned minPriority{1};
  constexpr unsigned maxPriority{26};

  auto result = lowerCaseValue(character) + minPriority;
  if (result < minPriority || result > maxPriority) {
    throw std::runtime_error("Invalid value");
  }
  return result;
}

constexpr auto upperCaseValue(char character) -> unsigned {
  return character - 'A';
}

constexpr auto isUpperCase(char character) {
  constexpr unsigned maxUpperCaseValue{'Z' - 'A'};
  auto value = upperCaseValue(character);
  return value <= maxUpperCaseValue;
}

constexpr auto upperCasePriority(char character) {
  constexpr unsigned minPriority{27};
  constexpr unsigned maxPriority{52};

  auto result = upperCaseValue(character) + minPriority;
  if (result < minPriority || result > maxPriority) {
    throw std::runtime_error("Invalid value");
  }
  return result;
}

constexpr auto priority(char sharedItem) -> unsigned {
  if (isLowerCase(sharedItem)) {
    return lowerCasePriority(sharedItem);
  }
  if (isUpperCase(sharedItem)) {
    return upperCasePriority(sharedItem);
  }
  throw std::runtime_error("Invalid character");
}

}  // namespace detail

constexpr auto sumScore(auto &&items) -> unsigned {
  auto priorities = items | std::views::transform([](auto character) {
                      return detail::priority(character);
                    }) |
                    std::views::common;
  return std::accumulate(priorities.begin(), priorities.end(), 0);
}
