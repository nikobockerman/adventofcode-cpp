#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>
#include <variant>

#include "example-input.hpp"
#include "input.hpp"
#include "problem.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

using T2022Day3 = TestFixture;

constexpr auto exampleInput = processExampleInput(R"input(
vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw
)input"sv);

TEST_F(T2022Day3, p1) {
  auto result = p1(exampleInput);
  EXPECT_EQ(std::get<uint64_t>(result), 157);
}

TEST_F(T2022Day3, p2) {
  auto result = p2(exampleInput);
  EXPECT_EQ(std::get<uint64_t>(result), 70);
}

TEST_F(T2022Day3, p1Correct) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 7848);
}

TEST_F(T2022Day3, p2Correct) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 2616);
}
