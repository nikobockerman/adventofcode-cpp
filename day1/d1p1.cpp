#include <algorithm>

#include "day1-common.hpp"
#include "program.hpp"

using namespace std::string_literals;

namespace {

auto _main(auto input) {
  auto calorieSums = resolveCalorieSums(input);
  return *std::max_element(calorieSums.cbegin(), calorieSums.cend());
}

}  // namespace

SHARED_MAIN
