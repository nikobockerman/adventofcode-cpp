cmake_minimum_required(VERSION 3.18)

project(adventofcode2022 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(common)

function(add_input_library targetName inputFile)
  file(READ ${inputFile} inputString)
  configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/input.in.hpp inputLib/input.hpp @ONLY)
  add_library(${targetName} INTERFACE)
  target_include_directories(${targetName} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/inputLib)
endfunction()

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
