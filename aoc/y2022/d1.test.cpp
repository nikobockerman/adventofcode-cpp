#include <gtest/gtest.h>

#include <cstdint>
#include <variant>

#include "input.hpp"
#include "problem.hpp"
#include "test.hpp"

using T2022Day1 = TestFixture;

TEST_F(T2022Day1, p1) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<int64_t>(result));
  EXPECT_EQ(std::get<int64_t>(result), 69836);
}

TEST_F(T2022Day1, p2) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<int64_t>(result));
  EXPECT_EQ(std::get<int64_t>(result), 207968);
}
