cmake_minimum_required(VERSION 3.18)

project(adventofcode2022 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)
find_package(fmt REQUIRED)
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

enable_testing()
include(GoogleTest)

add_subdirectory(common)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
