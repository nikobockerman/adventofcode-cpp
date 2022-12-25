#pragma once

#include <boost/program_options.hpp>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

enum class State { Ok, Help, Fail };

class Program {
 public:
  static auto create(std::string_view name,
                     boost::program_options::command_line_parser parser)
      -> std::pair<State, std::optional<Program>>;

  auto inputFile() -> auto & { return _file; }

  ~Program() = default;
  Program(const Program &) = delete;
  Program(Program &&) = default;
  auto operator=(const Program &) -> Program & = delete;
  auto operator=(Program &&) -> Program & = delete;

 private:
  explicit Program(std::ifstream file);

  std::ifstream _file;
};
