#include <algorithm>
#include <ranges>

#include "d1-common.hpp"
#include "program.hpp"

namespace {

auto _main(auto input) { return std::ranges::max(resolveCalorieSums(input)); }

}  // namespace

SHARED_MAIN
