#include <gtest/gtest.h>

#include <string>
#include <variant>

#include "input.hpp"
#include "problem.hpp"
#include "test.hpp"

using namespace std::string_literals;
using T2022Day5 = TestFixture;

TEST_F(T2022Day5, p1) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<std::string>(result));
  EXPECT_EQ(std::get<std::string>(result),
            "TLFGBZHCN"s);  // NOLINT(misc-include-cleaner)
}

TEST_F(T2022Day5, p2) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<std::string>(result));
  EXPECT_EQ(std::get<std::string>(result), "QRQFHFWCL"s);
}
