#include <gtest/gtest.h>

#include <cstdint>
#include <variant>

#include "input.hpp"
#include "problem.hpp"
#include "test.hpp"

using namespace std::string_literals;
using T2022Day6 = TestFixture;

TEST_F(T2022Day6, p1) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 1282);
}

TEST_F(T2022Day6, p2) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 3513);
}
