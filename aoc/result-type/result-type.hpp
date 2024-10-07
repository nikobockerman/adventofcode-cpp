#pragma once

#include <fmt/format.h>

#include <cstdint>
#include <string>
#include <variant>

using ResultType = std::variant<uint64_t, int64_t, std::string>;

namespace fmt {

template <>
struct formatter<ResultType> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) const {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const ResultType &result, FormatContext &ctx) const {
    if (std::holds_alternative<uint64_t>(result)) {
      return fmt::format_to(ctx.out(), "{}", std::get<uint64_t>(result));
    }
    if (std::holds_alternative<int64_t>(result)) {
      return fmt::format_to(ctx.out(), "{}", std::get<int64_t>(result));
    }
    if (std::holds_alternative<std::string>(result)) {
      return fmt::format_to(ctx.out(), "{}", std::get<std::string>(result));
    }
    throw std::runtime_error("Unknown result type");
  }
};

}  // namespace fmt
