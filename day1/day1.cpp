#include <algorithm>
#include <cassert>
#include <charconv>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <numeric>
#include <optional>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string>
#include <system_error>
#include <vector>

namespace {

std::optional<std::string> readLine(std::istream &stream) {
  std::string line;
  if (std::getline(stream, line)) {
    spdlog::debug("Read line: {}", line);
    return std::move(line);
  }
  spdlog::debug("EOL");
  return std::nullopt;
}

template <typename T> T convert(const std::string &str) {
  assert(!str.empty());

  T value;
  auto [ptr, ec]{std::from_chars(str.data(), str.data() + str.size(), value)};
  assert(ec == std::errc());
  spdlog::debug("Converted {} to {}", str, value);
  return value;
}

std::vector<unsigned> getSingleElfCalories(auto &getNextLine) {
  std::vector<unsigned> values;
  while (true) {
    auto line = getNextLine();
    if (!line.has_value()) {
      spdlog::debug("Got EOF");
      return values;
    }

    if (line.value().empty()) {
      spdlog::debug("Got empty line");
      return values;
    }

    values.emplace_back(convert<unsigned>(line.value()));
    spdlog::debug("Added value. Now contains: {}",
                  fmt::join(decltype(values){values}, ", "));
  }
}

std::vector<std::vector<unsigned>> getElfCalories(auto &getNextLine) {
  std::vector<std::vector<unsigned>> values;
  while (true) {
    auto elfValues = getSingleElfCalories(getNextLine);
    if (elfValues.empty()) {
      spdlog::debug("Received no values => EOF");
      return values;
    }
    values.emplace_back(std::move(elfValues));
  }
}

} // namespace

int main(int argc, const char *const argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " INPUT" << std::endl;
    return 1;
  }
  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("Starting");
  auto file = std::ifstream{argv[1]};
  auto getNextLine = [&file]() { return readLine(file); };
  auto allCalories = getElfCalories(getNextLine);

  std::vector<unsigned> sumCalories;
  std::transform(allCalories.cbegin(), allCalories.cend(),
                 std::back_inserter(sumCalories), [](auto &calories) {
                   return std::accumulate(calories.begin(), calories.end(), 0);
                 });

  auto result = std::max_element(sumCalories.cbegin(), sumCalories.cend());
  std::cout << "Result:" << std::endl << *result << std::endl;

  return 0;
}
