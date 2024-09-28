#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>
#include <variant>

#include "day-interface.hpp"
#include "example-input.hpp"
#include "input.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

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
  auto result = p1(example1Input);
  EXPECT_EQ(std::get<uint64_t>(result), 7);
}

TEST_F(T2022Day6, p1Example2) {
  auto result = p1(example2Input);
  EXPECT_EQ(std::get<uint64_t>(result), 5);
}

TEST_F(T2022Day6, p1Example3) {
  auto result = p1(example3Input);
  EXPECT_EQ(std::get<uint64_t>(result), 6);
}

TEST_F(T2022Day6, p1Example4) {
  auto result = p1(example4Input);
  EXPECT_EQ(std::get<uint64_t>(result), 10);
}

TEST_F(T2022Day6, p1Example5) {
  auto result = p1(example5Input);
  EXPECT_EQ(std::get<uint64_t>(result), 11);
}

TEST_F(T2022Day6, p2Example1) {
  auto result = p2(example1Input);
  EXPECT_EQ(std::get<uint64_t>(result), 19);
}

TEST_F(T2022Day6, p2Example2) {
  auto result = p2(example2Input);
  EXPECT_EQ(std::get<uint64_t>(result), 23);
}

TEST_F(T2022Day6, p2Example3) {
  auto result = p2(example3Input);
  EXPECT_EQ(std::get<uint64_t>(result), 23);
}

TEST_F(T2022Day6, p2Example4) {
  auto result = p2(example4Input);
  EXPECT_EQ(std::get<uint64_t>(result), 29);
}

TEST_F(T2022Day6, p2Example5) {
  auto result = p2(example5Input);
  EXPECT_EQ(std::get<uint64_t>(result), 26);
}

TEST_F(T2022Day6, p1Correct) {
  auto result = p1(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 1282);
}

TEST_F(T2022Day6, p2Correct) {
  auto result = p2(input);
  ASSERT_TRUE(std::holds_alternative<uint64_t>(result));
  EXPECT_EQ(std::get<uint64_t>(result), 3513);
}
