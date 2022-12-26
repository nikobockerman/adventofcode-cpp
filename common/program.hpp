#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <span>
#include <string_view>

// Implement this function and call SHARED_MAIN macro below it
// auto _main(std::ifstream input);
//
// That function should return a result.

#define SHARED_MAIN                                                       \
  auto main(int argc, char *argv[])->int {                                \
    if (argc < 0) {                                                       \
      throw std::runtime_error("No arguments");                           \
    }                                                                     \
    auto [state, input] =                                                 \
        program_private::initialize({argv, static_cast<unsigned>(argc)}); \
    switch (state) {                                                      \
      case program_private::State::Help:                                  \
        return 0;                                                         \
      case program_private::State::Fail:                                  \
        return 1;                                                         \
      case program_private::State::Ok:                                    \
        break;                                                            \
    }                                                                     \
                                                                          \
    auto result = _main(std::move(input.value()));                        \
    std::cout << "Result:" << std::endl << result << std::endl;           \
    return 0;                                                             \
  }

namespace program_private {

using Args = std::span<char *>;

enum class State { Ok, Help, Fail };

auto initialize(Args args) -> std::pair<State, std::optional<std::ifstream>>;

}  // namespace program_private
