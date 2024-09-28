#include <gtest/gtest.h>

#include <string>
#include <string_view>

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
  const auto exampleResult = "CMZ"s;  // NOLINT(misc-include-cleaner)
  verifyResult<std::string>(p1(exampleInput), exampleResult);
}

TEST_F(T2022Day5, p2) {
  const auto exampleResult = "MCD"s;
  verifyResult<std::string>(p2(exampleInput), exampleResult);
}

TEST_F(T2022Day5, p1Correct) {
  const auto correctResult = "TLFGBZHCN"s;
  verifyResult<std::string>(p1(input), correctResult);
}

TEST_F(T2022Day5, p2Correct) {
  const auto correctResult = "QRQFHFWCL"s;
  verifyResult<std::string>(p2(input), correctResult);
}
