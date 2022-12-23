#include "day1-common.hpp"

#include "convert.hpp"
#include "file-reader.hpp"

#include <charconv>
#include <fmt/ranges.h>
#include <numeric>
#include <spdlog/spdlog.h>

namespace {

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
