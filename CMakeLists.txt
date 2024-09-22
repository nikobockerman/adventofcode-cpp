cmake_minimum_required(VERSION 3.18)

project(adventofcode2022 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

enable_testing()
include(GoogleTest)

function(add_input_library targetName dayPart inputFile)
  file(READ ${inputFile} inputString)
  configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/input.in.hpp inputLib/${dayPart}/input.hpp @ONLY)
  add_library(${targetName} INTERFACE)
  target_include_directories(${targetName} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/inputLib/${dayPart})
endfunction()

function(add_solution_library targetNameVariable sourceFile)
  cmake_path(GET sourceFile STEM dayPart)
  cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME yearPart)
  set(targetName test-${yearPart}-${dayPart})

  set(inputFile input-${dayPart}.txt)
  add_input_library(${targetName}-input ${dayPart} ${inputFile})
  add_executable(${targetName} ${sourceFile})
  target_link_libraries(${targetName} PRIVATE GTest::gtest_main tools ${targetName}-input)
  gtest_discover_tests(${targetName})
  set(${targetNameVariable} ${targetName} PARENT_SCOPE)
endfunction()

# Allow long recursive constexpr evaluations project wide
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options("/constexpr:steps20000000")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("-fconstexpr-steps=20000000")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options("-fconstexpr-ops-limit=35000000")
endif()

# Make debug builds use runtime algorithms
link_libraries(debug enableRuntime)

add_subdirectory(aoc)
