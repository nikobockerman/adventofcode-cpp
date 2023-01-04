#include <stdexcept>

#include "common.hpp"
#include "d2-common.hpp"
#include "input.hpp"

namespace {

constexpr auto parseMe(char move) {
  switch (move) {
    case 'X':
      return Type::Rock;
    case 'Y':
      return Type::Paper;
    case 'Z':
      return Type::Scissors;
  }
  throw std::runtime_error("Unknown me type");
}

}  // namespace

auto main() -> int {
  enableDebugLogging();
  RUNTIME_CONSTEXPR auto result =
      sumScore(input, [](auto, auto move) { return parseMe(move); });
  printResult(result);
  return 0;
}
