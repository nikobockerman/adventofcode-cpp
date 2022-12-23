#include "file-reader.hpp"

#include <spdlog/spdlog.h>

auto readLine(std::istream &stream) -> std::optional<std::string> {
  std::string line;
  if (std::getline(stream, line)) {
    spdlog::debug("Read line: {}", line);
    return line;
  }
  spdlog::debug("EOL");
  return std::nullopt;
}
