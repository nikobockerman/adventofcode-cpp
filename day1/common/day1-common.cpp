#include "day1-common.hpp"

#include "file-reader.hpp"

#include <charconv>
#include <fmt/ranges.h>
#include <numeric>
#include <spdlog/spdlog.h>

namespace {

template <typename T> auto convert(const std::string &str) -> T {
  if (str.empty()) {
    throw std::runtime_error("Empty string to convert");
  }

  T value{};
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const auto *pastEnd = str.data() + str.size();
  auto [ptr, ec]{std::from_chars(str.data(), pastEnd, value)};
  if (ec != std::errc()) {
    throw std::runtime_error("Conversion failed");
  }
  spdlog::debug("Converted {} to {}", str, value);
  return value;
}

auto getSingleElfCalories(auto &getNextLine) -> std::vector<unsigned> {
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

auto getElfCalories(auto &getNextLine) -> std::vector<std::vector<unsigned>> {
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

auto resolveCalorieSums(std::istream &input) -> std::vector<unsigned> {
  auto getNextLine = [&input]() { return ::readLine(input); };
  auto allCalories = getElfCalories(getNextLine);

  std::vector<unsigned> calorieSums;
  std::transform(allCalories.cbegin(), allCalories.cend(),
                 std::back_inserter(calorieSums), [](auto &calories) {
                   return std::accumulate(calories.begin(), calories.end(), 0);
                 });
  return calorieSums;
}
