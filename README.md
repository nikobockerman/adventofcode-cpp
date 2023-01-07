# Advent Of Code problem solutions with C++

This repository contains solutions to some of the Advent Of Code problems
implemented in C++. This repository also serves a purpose of learning about new
C++ features and utilizing those in the solutions.

# Instructions for building

This project has some dependencies to other packages. Those dependencies are
managed using `conan`. Conan generates a toolchain file that allows CMake
project to easily find those dependencies.

CMakePresets.json contains official cmake configurations and serves as an
example for how to build this repository with CMake. These configurations assume
that `conan install` has been executed using `-if conan-install` flag in order
to get the `conan_toolchain.cmake` file generated to the specified directory.
