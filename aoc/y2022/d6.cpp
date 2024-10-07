#include <algorithm>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <string_view>
#include <vector>

#include "day-interface.hpp"
#include "result-type.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_literals;
using namespace std::string_view_literals;

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

auto p1(std::string_view input) -> ResultType {
  return firstDistinctWindow<4>(input);
}

auto p2(std::string_view input) -> ResultType {
  constexpr auto windowSize = 14;
  return firstDistinctWindow<windowSize>(input);
}
