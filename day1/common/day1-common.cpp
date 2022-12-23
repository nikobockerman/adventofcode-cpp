#include "day1-common.hpp"

#include <charconv>
#include <fmt/ranges.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include <spdlog/spdlog.h>

namespace po = boost::program_options;
using namespace std::string_literals;

namespace {

auto generic_options() -> boost::program_options::options_description {
  po::options_description generic("Generic options");
  generic.add_options()("help,h", "produce help message")(
      "verbose,v", "enable debug logging");
  return generic;
}

} // namespace

auto Program::create(std::string_view name,
                     boost::program_options::command_line_parser parser)
    -> std::pair<State, std::optional<Program>> {
  auto generic = generic_options();

  auto printUsage = [name, &generic](auto &stream) {
    stream << "Usage: " << name << " INPUT\n\n" << generic << std::endl;
  };

  po::positional_options_description positional;
  positional.add("input-file", 1);
  po::options_description hidden("");
  hidden.add_options()("input-file", po::value<std::string>());

  po::options_description parsedOptions("");
  parsedOptions.add(generic).add(hidden);

  po::variables_map vm;
  try {
    po::store(parser.options(parsedOptions).positional(positional).run(), vm);
  } catch (const po::error &error) {
    std::cerr << error.what() << std::endl << std::endl;
    printUsage(std::cerr);
    return {State::Fail, std::nullopt};
  }
  po::notify(vm);

  if (vm.contains("help")) {
    printUsage(std::cout);
    return {State::Help, std::nullopt};
  }

  if (vm.contains("verbose")) {
    spdlog::set_level(spdlog::level::debug);
  }

  if (!vm.contains("input-file")) {
    std::cerr << "INPUT file is needed\n\n";
    printUsage(std::cerr);
    return {State::Fail, std::nullopt};
  }

  auto filePath = vm["input-file"].as<std::string>();
  auto file = std::ifstream{filePath};
  if (!file.is_open()) {
    std::cerr << filePath << " doesn't exist" << std::endl;
    return {State::Fail, std::nullopt};
  }

  return {State::Ok, Program{std::move(file)}};
}

Program::Program(std::ifstream file) : _file{std::move(file)} {
  spdlog::debug("Program started");
}

namespace {

auto readLine(std::istream &stream) -> std::optional<std::string> {
  std::string line;
  if (std::getline(stream, line)) {
    spdlog::debug("Read line: {}", line);
    return line;
  }
  spdlog::debug("EOL");
  return std::nullopt;
}

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

auto Program::resolveCalorieSums() -> std::vector<unsigned> {
  auto getNextLine = [&file = _file]() { return readLine(file); };
  auto allCalories = getElfCalories(getNextLine);

  std::vector<unsigned> calorieSums;
  std::transform(allCalories.cbegin(), allCalories.cend(),
                 std::back_inserter(calorieSums), [](auto &calories) {
                   return std::accumulate(calories.begin(), calories.end(), 0);
                 });
  return calorieSums;
}
