#pragma once

#include <charconv>
#include <ranges>
#include <stdexcept>
#include <type_traits>

template <typename TResult, typename TRange>
  requires(std::ranges::contiguous_range<TRange> &&
           std::ranges::sized_range<TRange> &&
           std::is_same_v<std::ranges::range_value_t<TRange>, char>)
constexpr auto convert(TRange &&range) -> TResult {
  if (std::ranges::empty(std::forward<TRange>(range))) {
    throw std::runtime_error("Empty string to convert");
  }

  TResult value{};
  const auto *begin = &*range.begin();
  const auto *pastEnd = &*range.end();
  auto [ptr, ec]{std::from_chars(begin, pastEnd, value)};
  if (ec != std::errc()) {
    throw std::runtime_error("Conversion failed");
  }
  return value;
}
