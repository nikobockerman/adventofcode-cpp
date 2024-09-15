cmake_minimum_required(VERSION 3.28)

project(adventofcode2022 CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(common)
add_subdirectory(2022)

add_library(hello)
target_sources(hello PUBLIC FILE_SET CXX_MODULES FILES hello.cxx)
target_link_libraries(hello PRIVATE spdlog::spdlog)

add_library(problem)
target_sources(problem PUBLIC FILE_SET CXX_MODULES FILES problem.cxx)

add_executable(world main.cxx)
target_link_libraries(world PRIVATE hello problem fmt::fmt)
#target_sources(demo PUBLIC main.cpp)
