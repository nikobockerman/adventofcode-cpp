#pragma once

#include "@yearPart@-@dayPart@-solution_export.h"

// Other includes

#include <string_view>

#include "result-type.hpp"

// clang-format off
namespace @yearPart@::@dayPart@{

auto DAY_SOLUTION_EXPORT p1(std::string_view input) -> ResultType;
auto DAY_SOLUTION_EXPORT p2(std::string_view input) -> ResultType;

}
// clang-format on
