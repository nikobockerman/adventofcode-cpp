#include <algorithm>
#include <boost/exception/exception.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
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

namespace po = boost::program_options;

} // namespace

int main(int argc, const char *const argv[]) {
  po::options_description desc("Usage: day1 INPUT\n\n"
                               "Allowed options:");
  desc.add_options()("help,h", "produce help message")("verbose,v",
                                                       "enable debug logging");

  po::options_description hidden("Hidden");
  hidden.add_options()("input-file", po::value<std::string>());

  po::options_description cmdline("Cmd");
  cmdline.add(desc).add(hidden);

  po::positional_options_description p;
  p.add("input-file", 1);

  po::variables_map vm;
  try {
    po::store(po::command_line_parser{argc, argv}
                  .options(cmdline)
                  .positional(p)
                  .run(),
              vm);
  } catch (const po::error &error) {
    std::cerr << error.what() << std::endl << std::endl;
    std::cerr << desc << std::endl;
    return 1;
  }
  po::notify(vm);

  if (vm.contains("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  if (vm.contains("verbose")) {
    spdlog::set_level(spdlog::level::debug);
  }

  if (!vm.contains("input-file")) {
    std::cerr << "INPUT file is needed\n\n";
    std::cerr << desc << std::endl;
    return 1;
  }

  spdlog::debug("Starting");

  auto filePath = vm["input-file"].as<std::string>();
  auto file = std::ifstream{filePath};
  if (!file.is_open()) {
    std::cerr << filePath << " doesn't exist" << std::endl;
    return 1;
  }

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
