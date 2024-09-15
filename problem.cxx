module;
#include <dlfcn.h>

#include <filesystem>
#include <fstream>
#include <string>
export module Problem;

using namespace std::string_literals;

export enum class ProblemPart { Part1, Part2 };

export class ProblemLibrary {
 public:
  ProblemLibrary(const std::filesystem::path &libPath);
  ~ProblemLibrary();

  [[nodiscard]] auto p1(const std::string &input) -> int;
  [[nodiscard]] auto p2(const std::string &input) -> int;

  ProblemLibrary(const ProblemLibrary &) = default;
  ProblemLibrary(ProblemLibrary &&) = delete;
  auto operator=(const ProblemLibrary &) -> ProblemLibrary & = default;
  auto operator=(ProblemLibrary &&) -> ProblemLibrary & = delete;

 private:
  void *lib_;
};

export class Problem {
 public:
  Problem(int year, int day);

  [[nodiscard]] auto loadInput() const -> std::string;

  [[nodiscard]] auto loadLibrary() const -> ProblemLibrary;

 private:
  int year_;
  int day_;
};

ProblemLibrary::ProblemLibrary(const std::filesystem::path &libPath)
    : lib_(dlopen(libPath.c_str(), RTLD_LAZY)) {
  if (lib_ == nullptr) {
    throw std::runtime_error(dlerror());
  }
}

ProblemLibrary::~ProblemLibrary() {
  dlclose(lib_);
  lib_ = nullptr;
}

auto ProblemLibrary::p1(const std::string &input) -> int {
  dlerror();
  return reinterpret_cast<int (*)(const char *)>(dlsym(lib_, "p1"))(
      input.c_str());
}

auto ProblemLibrary::p2(const std::string &input) -> int {
  dlerror();
  auto func = reinterpret_cast<int (*)(const char *)>(dlsym(lib_, "p2"));

  return func(input.c_str());
}

Problem::Problem(int year, int day) : year_(year), day_(day) {}

void rtrim(std::string &str) {
  str.erase(
      std::find_if(str.rbegin(), str.rend(),
                   [](unsigned char chr) { return std::isspace(chr) == 0; })
          .base(),
      str.end());
}

auto Problem::loadInput() const -> std::string {
  const auto path = std::filesystem::current_path() / std::to_string(year_) /
                    ("day"s + std::to_string(day_)) / "input.txt";

  std::ifstream fStream(path);
  std::string contents((std::istreambuf_iterator<char>(fStream)),
                       std::istreambuf_iterator<char>());
  rtrim(contents);
  return contents;
}

auto Problem::loadLibrary() const -> ProblemLibrary {
  const auto year = std::to_string(year_);
  const auto day = std::to_string(day_);
  return std::filesystem::current_path() / "build" / "debug" / year /
         ("day" + day) / ("libproblem-" + year + "-day" + day + ".so");
}
