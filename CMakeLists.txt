cmake_minimum_required(VERSION 3.18)

project(adventofcode VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Configure maximum logging level
add_compile_definitions("$<$<CONFIG:Debug>:SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG>")
add_compile_definitions("$<$<CONFIG:Release>:SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_WARN>")

enable_testing()
include(GoogleTest)

add_subdirectory(aoc)
