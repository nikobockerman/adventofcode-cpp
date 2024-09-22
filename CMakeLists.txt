cmake_minimum_required(VERSION 3.18)

project(adventofcode2022 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

enable_testing()
include(GoogleTest)

function(set_year_part)
  cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME yearPart)
  set(yearPart ${yearPart} PARENT_SCOPE)
endfunction()

function(set_day_part day)
  set(dayPart d${day} PARENT_SCOPE)
endfunction()

function(add_input_library targetNameVariable day)
  set_year_part()
  set_day_part(${day})

  set(inputFile input-${dayPart}.txt)
  file(READ ${inputFile} inputString)
  configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/input.in.hpp inputLib/${dayPart}/input.hpp @ONLY)

  set(targetName ${yearPart}-${dayPart}-input)
  add_library(${targetName} INTERFACE)
  target_include_directories(${targetName} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/inputLib/${dayPart})
  set(${targetNameVariable} ${targetName} PARENT_SCOPE)
endfunction()

function(add_solution_library targetNameVariable day)
  set_year_part()
  set_day_part(${day})
  set(sourceFile ${dayPart}.cpp)

  set(targetName ${yearPart}-${dayPart}-solution)
  add_library(${targetName} STATIC ${sourceFile})
  set(${targetNameVariable} ${targetName} PARENT_SCOPE)
endfunction()

function(add_solution_test_executable targetNameVariable day)
  set_year_part()
  set_day_part(${day})
  set(sourceFile ${dayPart}.test.cpp)

  set(targetName ${yearPart}-${dayPart}-test)
  add_executable(${targetName} ${sourceFile})
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
