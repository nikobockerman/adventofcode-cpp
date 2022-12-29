#include "d2-common.hpp"
#include "program.hpp"

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

auto _main(auto input) {
  return sumScore(input, [](auto, auto move) { return parseMe(move); });
}

}  // namespace

SHARED_MAIN
