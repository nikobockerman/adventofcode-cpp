#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>
#include <variant>

#include "day-interface.hpp"
#include "example-input.hpp"
#include "input.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

using T2022Day4 = TestFixture;

constexpr auto exampleInput = processExampleInput(R"input(
2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8
)input"sv);

TEST_F(T2022Day4, p1) {
  auto result = p1(exampleInput);
  EXPECT_EQ(std::get<int64_t>(result), 2);
}

TEST_F(T2022Day4, p2) {
  auto result = p2(exampleInput);
  EXPECT_EQ(std::get<int64_t>(result), 4);
}

TEST_F(T2022Day4, p1Correct) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<int64_t>(result));
  EXPECT_EQ(std::get<int64_t>(result), 536);
}

TEST_F(T2022Day4, p2Correct) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<int64_t>(result));
  EXPECT_EQ(std::get<int64_t>(result), 845);
}
