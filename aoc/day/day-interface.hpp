#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <variant>

using ResultType = std::variant<uint64_t, int64_t, std::string>;

auto p1(std::string_view input) -> ResultType;
auto p2(std::string_view input) -> ResultType;
