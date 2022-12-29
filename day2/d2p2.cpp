#include <stdexcept>

#include "d2-common.hpp"
#include "program.hpp"

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

constexpr auto _main(auto input) { return sumScore(input, parseMe); }

}  // namespace

SHARED_MAIN
