#include <fmt/format.h>

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <string_view>

#include "aoc-config.hpp"
#include "result-type.hpp"
#include "solution-includes.hpp"

using namespace std::string_literals;

auto answers() {
  static const std::map<int, std::map<int, std::map<int, ResultType>>>
      answers_ = {{2022,
                   {{1, {{1, uint64_t{69'836}}, {2, uint64_t{207'968}}}},
                    {2, {{1, uint64_t{8'890}}, {2, uint64_t{10'238}}}},
                    {3, {{1, uint64_t{7'848}}, {2, uint64_t{2'616}}}},
                    {4, {{1, int64_t{536}}, {2, int64_t{845}}}},
                    {5,
                     {{1, "TLFGBZHCN"s},  // NOLINT(misc-include-cleaner)
                      {2, "QRQFHFWCL"s}}},
                    {6, {{1, uint64_t{1'282}}, {2, uint64_t{3'513}}}}}}};
  return answers_;
}

auto problems() {
  static const std::map<
      int,
      std::map<int, std::map<int, std::function<ResultType(std::string_view)>>>>
      problems_ = {{2022,
                    {{1, {{1, y2022::d1::p1}, {2, y2022::d1::p2}}},
                     {2, {{1, y2022::d2::p1}, {2, y2022::d2::p2}}},
                     {3, {{1, y2022::d3::p1}, {2, y2022::d3::p2}}},
                     {4, {{1, y2022::d4::p1}, {2, y2022::d4::p2}}},
                     {5, {{1, y2022::d5::p1}, {2, y2022::d5::p2}}},
                     {6, {{1, y2022::d6::p1}, {2, y2022::d6::p2}}}}}};
  return problems_;
}

auto inputFilesRootDir() -> std::filesystem::path {
  return std::filesystem::path{sourceDirRoot} / "aoc";
}

void rtrim(std::string& str) {
  str.erase(
      std::find_if(str.rbegin(), str.rend(),
                   [](unsigned char chr) { return std::isspace(chr) == 0; })
          .base(),
      str.end());
}

auto readInputFile(int year, int day) -> std::string {
  auto path = inputFilesRootDir() / fmt::format("y{}", year) /
              fmt::format("input-d{}.txt", day);
  std::ifstream fStream(path);
  std::string contents((std::istreambuf_iterator<char>(fStream)),
                       std::istreambuf_iterator<char>());
  rtrim(contents);
  return contents;
}

auto main() -> int {  // NOLINT(bugprone-exception-escape)
  bool success = true;
  for (auto const& [year, answerDays] : answers()) {
    for (auto const& [day, answerProblems] : answerDays) {
      auto input = readInputFile(year, day);

      for (auto const& [problem, correctAnswer] : answerProblems) {
        auto msg = fmt::format("{} {:2} {}: ", year, day, problem);

        auto problemFunc = problems().at(year).at(day).at(problem);

        ResultType result = problemFunc(input);

        if (result != correctAnswer) {
          msg += fmt::format("FAIL: Incorrect answer: {}. Correct is: {}",
                             result, correctAnswer);
          success = false;
        } else {
          msg += "PASS";
        }
        std::cout << msg << '\n';
      }
    }
  }
  if (success) {
    std::cout << "Finished with all passing.\n";
    return 0;
  }
  std::cout << "Finished with failures.\n";
  return 1;
}
