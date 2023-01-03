#pragma once

#include <algorithm>
#include <functional>
#include <ranges>
#include <string_view>
#include <vector>

#ifdef __cpp_lib_ranges_fold
#warning "Replace most std::accumulate usages with std::ranges::fold"
#endif

template <typename TValue, typename TDivider>
constexpr auto modulo(TValue value, TDivider divider) -> TValue {
  return value % divider;
}

auto split(std::string_view str, char separator)
    -> std::vector<std::string_view>;

auto split(const std::vector<std::string_view>& container,
           const std::function<bool(std::string_view)>& isSeparator)
    -> std::vector<std::vector<std::string_view>>;

auto group(const std::vector<std::string_view>& container,
           std::size_t groupSize) -> std::vector<std::vector<std::string_view>>;

constexpr auto splitLinesUntilEmpty(auto&& range) {
  constexpr std::string_view lineBreak{"\n"};
  return range | std::views::split(lineBreak) |
         std::views::take_while([](const auto& line) { return !line.empty(); });
}

#ifdef __cpp_lib_ranges_to_container
//#error "Use std::ranges::to<std::vector> directly instead"
#else
// Note: use of __adaptor may mean that this only works with GCC 12.2.0.
struct _ToVector : public std::views::__adaptor::_RangeAdaptorClosure {
  constexpr auto operator() [[nodiscard]] (auto&& range) const {
    auto commonView = range | std::views::common;
    return std::vector(commonView.begin(), commonView.end());
  }

  static constexpr bool _S_has_simple_call_op = true;
};

inline constexpr _ToVector toVector;
#endif

constexpr auto vectorSet(auto&& range) {
  auto vector = range | std::ranges::to<std::vector>();
  std::ranges::sort(vector);
  auto ret = std::ranges::unique(vector);
  vector.erase(ret.begin(), ret.end());
  return vector;
}

#ifdef __cpp_lib_ranges_chunk
//#error "Use views::chunk directly"
#else
struct _CustomChunkView
    : public std::views::__adaptor::_RangeAdaptor<_CustomChunkView> {
  constexpr auto operator()
      [[nodiscard]] (auto&& range, auto&& groupSize) const {
    auto vector = range | toVector;
    auto size = vector.size();
    return std::views::iota(0) | std::views::transform([groupSize](auto index) {
             return index * groupSize;
           }) |
           std::views::take_while(
               [size](auto beginOffset) { return beginOffset < size; }) |
           std::views::transform([vector, size, groupSize](auto beginOffset) {
             auto takeSize = std::min(groupSize, size - beginOffset);
             return vector | std::views::drop(beginOffset) |
                    std::views::take(takeSize);
           });
  }

  using _RangeAdaptor<_CustomChunkView>::operator();
  static constexpr int _S_arity = 2;
  static constexpr bool _S_has_simple_extra_args = true;
  static constexpr bool _S_has_simple_call_op = true;
};

inline constexpr _CustomChunkView customChunkView;
#endif
