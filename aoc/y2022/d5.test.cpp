#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <variant>

#include "day-interface.hpp"
#include "example-input.hpp"
#include "input.hpp"
#include "test.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

using T2022Day5 = TestFixture;

constexpr auto exampleInput = processExampleInput(R"input(
    [D]
[N] [C]
[Z] [M] [P]
 1   2   3

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2
)input"sv);

TEST_F(T2022Day5, p1) {
  auto result = p1(exampleInput);
  EXPECT_EQ(std::get<std::string>(result),
            "CMZ"s);  // NOLINT(misc-include-cleaner)
}

TEST_F(T2022Day5, p2) {
  auto result = p2(exampleInput);
  EXPECT_EQ(std::get<std::string>(result),
            "MCD"s);  // NOLINT(misc-include-cleaner)
}

TEST_F(T2022Day5, p1Correct) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<std::string>(result));
  EXPECT_EQ(std::get<std::string>(result),
            "TLFGBZHCN"s);  // NOLINT(misc-include-cleaner)
}

TEST_F(T2022Day5, p2Correct) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<std::string>(result));
  EXPECT_EQ(std::get<std::string>(result), "QRQFHFWCL"s);
}
