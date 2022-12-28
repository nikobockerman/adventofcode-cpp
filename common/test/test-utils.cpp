#include <gtest/gtest.h>

#include "utils.hpp"

// NOLINTNEXTLINE
TEST(strings, test_split) {
  std::string_view str{"one two"};
  auto result = split(str, ' ');
  auto expected = std::vector<std::string_view>{"one", "two"};
  EXPECT_EQ(result, expected);
}

// NOLINTNEXTLINE
TEST(group, test_group) {
  std::vector<std::string_view> container{"one",  "two",  "three",
                                          "four", "five", "six"};
  auto result = group(container, 2);
  auto expected = std::vector<std::vector<std::string_view>>{
      {"one", "two"}, {"three", "four"}, {"five", "six"}};
  EXPECT_EQ(result, expected);
}
