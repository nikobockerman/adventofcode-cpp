#include <stdexcept>

#include "common.hpp"
#include "d2-common.hpp"
#include "input.hpp"

namespace {

constexpr auto losingType(Type opponent) {
  switch (opponent) {
    case Type::Paper:
      return Type::Rock;
    case Type::Scissors:
      return Type::Paper;
    case Type::Rock:
      return Type::Scissors;
  }
  throw std::runtime_error("Unknown opponent type for losing");
}

constexpr auto winningType(Type opponent) {
  switch (opponent) {
    case Type::Paper:
      return Type::Scissors;
    case Type::Scissors:
      return Type::Rock;
    case Type::Rock:
      return Type::Paper;
  }
  throw std::runtime_error("Unknown opponent type for winning");
}

constexpr auto parseMe(Type opponent, char move) {
  switch (move) {
    case 'X':
      return losingType(opponent);
    case 'Y':
      return opponent;
    case 'Z':
      return winningType(opponent);
  }
  throw std::runtime_error("Unknown me type");
}

}  // namespace

auto main() -> int {
  enableDebugLogging();
  constexpr auto result = sumScore(
      input, [](auto opponent, auto move) { return parseMe(opponent, move); });
  printResult(result);
  return 0;
}
