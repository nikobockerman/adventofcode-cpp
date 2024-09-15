import Hello;
// import y2022.d1;
import Problem;

#include <fmt/format.h>

#include <filesystem>
#include <iostream>
#include <map>
#include <ranges>

namespace {}

const std::map<int, std::map<int, std::map<int, int>>> answers = {
    {2022, {{1, {{1, 69836}, {2, 207968}}}}}};

auto main() -> int {
  hello();
  const int year = 2022;
  const int day = 1;
  std::cout << "Current path: " << std::filesystem::current_path() << std::endl;
  Problem problem(year, day);
  auto input = problem.loadInput();
  auto library = problem.loadLibrary();
  bool success = true;
  for (auto problem : std::views::iota(1, 3)) {
    auto correctAnswer = answers.at(year).at(day).at(problem);
    int result = 0;
    switch (problem) {
      case 1:
        result = library.p1(input);
        break;
      case 2:
        result = library.p2(input);
        break;
      default:
        throw std::runtime_error("Invalid problem number");
    }
    auto msg = fmt::format("Year {} Day {:2} Problem {}: ", year, day, problem);
    if (result != correctAnswer) {
      msg += fmt::format("FAIL: Incorrect answer: {}. Correct is: {}", result,
                         correctAnswer);
      success = false;
    } else {
      msg += "PASS";
    }
    std::cout << msg << std::endl;
  }
  if (success) {
    std::cout << "Finished with all passing." << std::endl;
    return 0;
  }
  std::cout << "Finished with failures." << std::endl;
  return 1;
}
