#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>
#include <variant>

#include "example-input.hpp"
#include "input.hpp"
#include "problem.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

using T2022Day1 = TestFixture;

constexpr auto exampleInput = processExampleInput(R"input(
1000
2000
3000

4000

5000
6000

7000
8000
9000

10000
)input"sv);

TEST_F(T2022Day1, p1) {
  auto result = p1(exampleInput);
  EXPECT_EQ(std::get<int64_t>(result), 24000);
}

TEST_F(T2022Day1, p2) {
  auto result = p2(exampleInput);
  EXPECT_EQ(std::get<int64_t>(result), 45000);
}

TEST_F(T2022Day1, p1Correct) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<int64_t>(result));
  EXPECT_EQ(std::get<int64_t>(result), 69836);
}

TEST_F(T2022Day1, p2Correct) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<int64_t>(result));
  EXPECT_EQ(std::get<int64_t>(result), 207968);
}
