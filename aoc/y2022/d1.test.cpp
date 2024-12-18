#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>

#include "day-interface-y2022-d1.hpp"
#include "example-input.hpp"
#include "test.hpp"

using namespace std::string_view_literals;

using y2022::d1::p1;
using y2022::d1::p2;

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
  verifyResult<uint64_t>(p1(exampleInput), exampleResult);
}

TEST_F(T2022Day1, p2) {
  constexpr auto exampleResult = 45'000;
  verifyResult<uint64_t>(p2(exampleInput), exampleResult);
}
