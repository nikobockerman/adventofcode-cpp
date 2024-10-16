#include <gtest/gtest.h>

#include <string>
#include <string_view>

#include "day-interface-y2022-d5.hpp"
#include "example-input.hpp"
#include "test.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

using y2022::d5::p1;
using y2022::d5::p2;

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
