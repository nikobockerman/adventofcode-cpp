#include "common.hpp"
#include "input.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_literals;
using namespace std::string_view_literals;

using T2022_day6 = TestFixture;

namespace {

template <std::size_t windowSize>
constexpr auto firstDistinctWindow(auto &&range) {
  auto notStarts =
      range | views::slide(windowSize) | views::take_while([](auto &&window) {
        auto vector = window | ranges::to<std::vector>();
        ranges::sort(vector);
        return ranges::adjacent_find(vector) != vector.end();
      });
  return ranges::distance(notStarts) + windowSize;
}

}  // namespace

TEST_F(T2022_day6, part1) {
  RUNTIME_CONSTEXPR auto result = firstDistinctWindow<4>(input);
  EXPECT_EQ(result, 1282);
}

TEST_F(T2022_day6, part2) {
  constexpr auto windowSize = 14;
  RUNTIME_CONSTEXPR auto result = firstDistinctWindow<windowSize>(input);
  EXPECT_EQ(result, 3513);
}
