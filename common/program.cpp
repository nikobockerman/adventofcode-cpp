#include "program.hpp"

#include <iostream>
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
