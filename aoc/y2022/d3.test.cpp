#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>

#include "day-interface-y2022-d3.hpp"
#include "example-input.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

using y2022::d3::p1;
using y2022::d3::p2;

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
