#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>

#include "day-interface-y2022-d6.hpp"
#include "example-input.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

using y2022::d6::p1;
using y2022::d6::p2;

using T2022Day6 = TestFixture;

constexpr auto example1Input = processExampleInput(R"input(
mjqjpqmgbljsphdztnvjfqwrcgsmlb
)input"sv);

constexpr auto example2Input = processExampleInput(R"input(
bvwbjplbgvbhsrlpgdmjqwftvncz
)input"sv);

constexpr auto example3Input = processExampleInput(R"input(
nppdvjthqldpwncqszvftbrmjlhg
)input"sv);

constexpr auto example4Input = processExampleInput(R"input(
nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg
)input"sv);

constexpr auto example5Input = processExampleInput(R"input(
zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw
)input"sv);

TEST_F(T2022Day6, p1Example1) {
  constexpr auto exampleResult = 7;
  verifyResult<uint64_t>(p1(example1Input), exampleResult);
}

TEST_F(T2022Day6, p1Example2) {
  constexpr auto exampleResult = 5;
  verifyResult<uint64_t>(p1(example2Input), exampleResult);
}

TEST_F(T2022Day6, p1Example3) {
  constexpr auto exampleResult = 6;
  verifyResult<uint64_t>(p1(example3Input), exampleResult);
}

TEST_F(T2022Day6, p1Example4) {
  constexpr auto exampleResult = 10;
  verifyResult<uint64_t>(p1(example4Input), exampleResult);
}

TEST_F(T2022Day6, p1Example5) {
  constexpr auto exampleResult = 11;
  verifyResult<uint64_t>(p1(example5Input), exampleResult);
}

TEST_F(T2022Day6, p2Example1) {
  constexpr auto exampleResult = 19;
  verifyResult<uint64_t>(p2(example1Input), exampleResult);
}

TEST_F(T2022Day6, p2Example2) {
  constexpr auto exampleResult = 23;
  verifyResult<uint64_t>(p2(example2Input), exampleResult);
}

TEST_F(T2022Day6, p2Example3) {
  constexpr auto exampleResult = 23;
  verifyResult<uint64_t>(p2(example3Input), exampleResult);
}

TEST_F(T2022Day6, p2Example4) {
  constexpr auto exampleResult = 29;
  verifyResult<uint64_t>(p2(example4Input), exampleResult);
}

TEST_F(T2022Day6, p2Example5) {
  constexpr auto exampleResult = 26;
  verifyResult<uint64_t>(p2(example5Input), exampleResult);
}
