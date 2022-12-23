#pragma once

#include <charconv>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string_view>

template <typename T> auto convert(const std::string_view &str) -> T {
  if (str.empty()) {
    throw std::runtime_error("Empty string to convert");
  }

  T value{};
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const auto *pastEnd = str.data() + str.size();
  auto [ptr, ec]{std::from_chars(str.data(), pastEnd, value)};
  if (ec != std::errc()) {
    throw std::runtime_error("Conversion failed");
  }
  spdlog::debug("Converted {} to {}", str, value);
  return value;
}
