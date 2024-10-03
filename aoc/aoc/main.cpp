#include <fmt/format.h>

#include <boost/dll/runtime_symbol_info.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>

#include "aoc-config.hpp"
#include "y2022-d1-interface.hpp"
#include "y2022-d2-interface.hpp"

namespace {}

auto answers() {
  static const std::map<int, std::map<int, std::map<int, ResultType>>>
      answers_ = {{2022,
                   {
                       {1, {{1, uint64_t{69'836}}, {2, uint64_t{207'968}}}},
                       {2, {{1, uint64_t{8'890}}, {2, uint64_t{10'238}}}},
                   }}};
  return answers_;
}

auto problems() {
  static const std::map<
      int,
      std::map<int, std::map<int, std::function<ResultType(std::string_view)>>>>
      problems_ = {{2022,
                    {{1, {{1, y2022::d1::p1}, {2, y2022::d1::p2}}},
                     {2, {{1, y2022::d2::p1}, {2, y2022::d2::p2}}}}}};
  return problems_;
}

auto executablePath() -> std::filesystem::path {
  static auto path =
      std::filesystem::path{boost::dll::program_location().native()};
  return path;
}

auto inputFilesDir() -> std::filesystem::path {
  return (executablePath().parent_path() / binToDataPath).lexically_normal() /
         projectName / "inputs";
}

void rtrim(std::string& str) {
  str.erase(
      std::find_if(str.rbegin(), str.rend(),
                   [](unsigned char chr) { return std::isspace(chr) == 0; })
          .base(),
      str.end());
}

auto readInputFile(int year, int day) -> std::string {
  auto path = inputFilesDir() / fmt::format("y{}", year) /
              fmt::format("input-d{}.txt", day);

  std::ifstream fStream(path);
  std::string contents((std::istreambuf_iterator<char>(fStream)),
                       std::istreambuf_iterator<char>());
  rtrim(contents);
  return contents;
}

auto main() -> int {  // NOLINT(bugprone-exception-escape)
  std::cout << "Current path: " << std::filesystem::current_path() << std::endl;
  std::cout << "Input files directory: " << inputFilesDir() << std::endl;
  bool success = true;
  for (auto const& [year, answerDays] : answers()) {
    for (auto const& [day, answerProblems] : answerDays) {
      for (auto const& [problem, correctAnswer] : answerProblems) {
        auto msg =
            fmt::format("Year {} Day {:2} Problem {}: ", year, day, problem);

        auto problemFunc = problems().at(year).at(day).at(problem);

        auto input = readInputFile(year, day);
        ResultType result = problemFunc(input);
        if (result != correctAnswer) {
          msg += fmt::format("FAIL: Incorrect answer: {}. Correct is: {}",
                             result, correctAnswer);
          success = false;
        } else {
          msg += "PASS";
        }
        std::cout << msg << std::endl;
      }
    }
  }
  if (success) {
    std::cout << "Finished with all passing." << std::endl;
    return 0;
  }
  std::cout << "Finished with failures." << std::endl;
  return 1;
}
