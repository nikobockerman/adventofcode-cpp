#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>
#include <variant>

#include "example-input.hpp"
#include "input.hpp"
#include "problem.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

using T2022Day2 = TestFixture;

constexpr auto exampleInput = processExampleInput(R"input(
A Y
B X
C Z
)input"sv);

TEST_F(T2022Day2, p1) {
  auto result = p1(exampleInput);
  EXPECT_EQ(std::get<uint64_t>(result), 15);
}

TEST_F(T2022Day2, p2) {
  auto result = p2(exampleInput);
  EXPECT_EQ(std::get<uint64_t>(result), 12);
}

TEST_F(T2022Day2, p1Correct) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 8890);
}

TEST_F(T2022Day2, p2Correct) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 10238);
}
