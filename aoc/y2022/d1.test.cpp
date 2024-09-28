#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>

#include "day-interface.hpp"
#include "example-input.hpp"
#include "input.hpp"
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
  constexpr auto exampleResult = 24'000;
  verifyResult<int64_t>(p1(exampleInput), exampleResult);
}

TEST_F(T2022Day1, p2) {
  constexpr auto exampleResult = 45'000;
  verifyResult<int64_t>(p2(exampleInput), exampleResult);
}

TEST_F(T2022Day1, p1Correct) {
  constexpr auto correctResult = 69'836;
  verifyResult<int64_t>(p1(input), correctResult);
}

TEST_F(T2022Day1, p2Correct) {
  constexpr auto correctResult = 207'968;
  verifyResult<int64_t>(p2(input), correctResult);
}
