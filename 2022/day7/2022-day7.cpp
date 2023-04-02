#include <numeric>

#include "common.hpp"
#include "input.hpp"

namespace ranges = std::ranges;
namespace views = std::views;
using namespace std::string_literals;
using namespace std::string_view_literals;

using T2022_day7 = TestFixture;

namespace {

class Directory {
 public:
  std::vector<Directory> subdirectories;
  std::size_t sumSizeFiles;
};

auto solve1() {
  auto pathChangesAndListings =
      splitLinesUntilEmpty(input) |
      views::chunk_by([](const auto &prev, const auto &next) {
        return ranges::starts_with(prev, "$ "sv) ||
               !ranges::starts_with(next, "$ "sv);
      }) |
      views::transform([](auto &&part) {
        auto parts = part |
                     views::chunk_by([](const auto &prev, const auto &next) {
                       return !ranges::starts_with(prev, "$ "sv) ||
                              ranges::starts_with(next, "$ "sv);
                     }) |
                     ranges::to<std::vector>();
        auto &commands = parts.at(0);
        auto path = ranges::fold_left(
            commands | views::take_while([](const auto &cmd) {
              return !ranges::equal(cmd, "$ ls");
            }),
            std::vector<std::string_view>{}, [](auto &&path, auto &&next) {
              path.emplace_back(next);
              return path;
            });
        return std::make_tuple(std::move(path), std::move(parts.at(1)));
      });

  // auto [finalDir, pathsAndListings] = std::accumulate(range.begin(),
  // range.end(), ))
  for (const auto &part : pathChangesAndListings) {
    // auto cmd = *part.begin();
    // if (currentPath.empty() && !ranges::equal(cmd, "$ cd /"sv)) {
    //   throw std::runtime_error("Unexpected initial path");
    // }
    // if (ranges::starts_with(cmd, "$ cd "sv)) {
    //   auto path = cmd | views::drop(5);
    //   if (ranges::equal(path, ".."sv)) {
    //     currentPath.pop_back();
    //   } else {
    //     currentPath.emplace_back(path);
    //   }
    // } else if (ranges::equal(cmd, "$ ls")) {
    // }
    // for (auto line) {
    // }
    logd("Parts: {}", part);
  }

  return 1;
}

}  // namespace

TEST_F(T2022_day7, part1) {
  RUNTIME_CONSTEXPR auto result = solve1();
  EXPECT_EQ(result, 0);
}

TEST_F(T2022_day7, part2) {
  RUNTIME_CONSTEXPR auto result = 1;
  EXPECT_EQ(result, 0);
}
