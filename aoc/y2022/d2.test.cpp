#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>

#include "day-interface.hpp"
#include "example-input.hpp"
#include "input.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

using T2022Day2 = TestFixture;

constexpr auto exampleInput = processExampleInput(R"input(
A Y
B X
C Z
)input"sv);

TEST_F(T2022Day2, p1) {
  constexpr auto exampleResult = 15;
  verifyResult<uint64_t>(p1(exampleInput), exampleResult);
}

TEST_F(T2022Day2, p2) {
  constexpr auto exampleResult = 12;
  verifyResult<uint64_t>(p2(exampleInput), exampleResult);
}

TEST_F(T2022Day2, p1Correct) {
  constexpr auto correctResult = 8'890;
  verifyResult<uint64_t>(p1(input), correctResult);
}

TEST_F(T2022Day2, p2Correct) {
  constexpr auto correctResult = 10'238;
  verifyResult<uint64_t>(p2(input), correctResult);
}
