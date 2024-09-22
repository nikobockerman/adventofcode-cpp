#include <gtest/gtest.h>

#include <cstdint>
#include <variant>

#include "input.hpp"
#include "problem.hpp"
#include "test.hpp"

using T2022Day3 = TestFixture;

TEST_F(T2022Day3, p1) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 7848);
}

TEST_F(T2022Day3, p2) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 2616);
}
