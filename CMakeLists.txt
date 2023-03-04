cmake_minimum_required(VERSION 3.18)

project(adventofcode2022 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

enable_testing()
include(GoogleTest)

function(add_input_library targetName inputFile)
  file(READ ${inputFile} inputString)
  configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/input.in.hpp inputLib/input.hpp @ONLY)
  add_library(${targetName} INTERFACE)
  target_include_directories(${targetName} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/inputLib)
endfunction()

function(get_target_name targetNameVariable)
  cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME day)
  cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH yearDir)
  cmake_path(GET yearDir FILENAME year)
  set(${targetNameVariable} test-${year}-${day} PARENT_SCOPE)
endfunction()

function(add_solution_library targetNameVariable sourceFile)
  get_target_name(name)
  add_input_library(${name}-input input)
  add_executable(${name} ${sourceFile})
  target_link_libraries(${name} PRIVATE GTest::gtest_main common ${name}-input)
  gtest_discover_tests(${name})
  set(${targetNameVariable} ${name} PARENT_SCOPE)
endfunction()

# Allow long recursive constexpr evaluations project wide
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options("/constexpr:steps20000000")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("-fconstexpr-steps=20000000")
endif()

# Make debug builds use runtime algorithms
link_libraries(debug enableRuntime)

add_subdirectory(common)
add_subdirectory(2022)
