configure_file(aoc-config.in.hpp aoc-config.hpp @ONLY)

add_executable(aoc main.cpp)
target_include_directories(aoc PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(aoc PRIVATE fmt::fmt result-type all-solutions)
