#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>

#include "day-interface.hpp"
#include "example-input.hpp"
#include "input.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

using T2022Day3 = TestFixture;

constexpr auto exampleInput = processExampleInput(R"input(
vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw
)input"sv);

TEST_F(T2022Day3, p1) {
  constexpr auto exampleResult = 157;
  verifyResult<uint64_t>(p1(exampleInput), exampleResult);
}

TEST_F(T2022Day3, p2) {
  constexpr auto exampleResult = 70;
  verifyResult<uint64_t>(p2(exampleInput), exampleResult);
}

TEST_F(T2022Day3, p1Correct) {
  constexpr auto correctResult = 7'848;
  verifyResult<uint64_t>(p1(input), correctResult);
}

TEST_F(T2022Day3, p2Correct) {
  constexpr auto correctResult = 2'616;
  verifyResult<uint64_t>(p2(input), correctResult);
}
