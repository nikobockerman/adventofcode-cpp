#pragma once

#include <functional>
#include <string_view>
#include <vector>

template <typename TValue, typename TDivider>
auto modulo(TValue value, TDivider divider) -> TValue {
  return value % divider;
}

auto split(std::string_view str, char separator)
    -> std::vector<std::string_view>;

auto split(const std::vector<std::string_view>& container,
           const std::function<bool(std::string_view)>& isSeparator)
    -> std::vector<std::vector<std::string_view>>;

auto group(const std::vector<std::string_view>& container,
           std::size_t groupSize) -> std::vector<std::vector<std::string_view>>;
