#include "program.hpp"

#include <spdlog/spdlog.h>

#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
namespace po = boost::program_options;

using namespace std::string_literals;

namespace {

auto generic_options() -> boost::program_options::options_description {
  po::options_description generic("Generic options");
  generic.add_options()("help,h", "produce help message")(
      "verbose,v", "enable debug logging");
  return generic;
}

}  // namespace

auto program_private::initialize(Args args)
    -> std::pair<State, std::optional<std::ifstream>> {
  if (args.empty()) {
    throw std::runtime_error("At least program name required in args");
  }

  if (args.size() > std::numeric_limits<int>::max()) {
    throw std::invalid_argument("args");
  }
  po::command_line_parser parser{static_cast<int>(args.size()), args.data()};

  auto executable_path = fs::path{args.front()};
  auto executable_name = executable_path.filename();
  auto generic = generic_options();

  auto printUsage = [&executable_name, &generic](auto &stream) {
    stream << "Usage: " << executable_name << " INPUT\n\n"
           << generic << std::endl;
  };

  auto defaultInputFile =
      executable_path.parent_path().lexically_normal() / "input";

  po::positional_options_description positional;
  positional.add("input-file", 1);
  po::options_description hidden("");
  hidden.add_options()(
      "input-file", po::value<std::string>()->default_value(defaultInputFile));

  po::options_description parsedOptions("");
  parsedOptions.add(generic).add(hidden);

  po::variables_map variables;
  try {
    po::store(parser.options(parsedOptions).positional(positional).run(),
              variables);
  } catch (const po::error &error) {
    std::cerr << error.what() << std::endl << std::endl;
    printUsage(std::cerr);
    return {State::Fail, std::nullopt};
  }
  po::notify(variables);

  if (variables.contains("help")) {
    printUsage(std::cout);
    return {State::Help, std::nullopt};
  }

  if (variables.contains("verbose")) {
    spdlog::set_level(spdlog::level::debug);
  }

  if (!variables.contains("input-file")) {
    std::cerr << "INPUT file is needed\n\n";
    printUsage(std::cerr);
    return {State::Fail, std::nullopt};
  }

  auto filePath = variables["input-file"].as<std::string>();
  auto file = std::ifstream{filePath};
  if (!file.is_open()) {
    std::cerr << filePath << " doesn't exist" << std::endl;
    return {State::Fail, std::nullopt};
  }

  spdlog::debug("Program started");
  return {State::Ok, std::move(file)};
}
