cmake_minimum_required(VERSION 3.18)

project(adventofcode2022 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(spdlog REQUIRED)

add_subdirectory(day1)
