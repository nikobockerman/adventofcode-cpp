# Advent Of Code problem solutions with C++

This repository contains solutions to some of the Advent Of Code problems
implemented in C++. This repository also serves a purpose of learning about new
C++ features and utilizing those in the solutions.

# Instructions for building

This project has some dependencies to other packages. Those dependencies are
managed using `conan`. Conan generates a toolchain file that allows CMake
project to easily find those dependencies.

`conan` is a Python package and `poetry` is used to install it.

## Installing dependencies with Conan

CMakePresets.json contains official cmake configurations and serves as an
example for how to build this repository with CMake. These configurations assume
that `poetry run conan install .` has been executed by applying
`tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']"` conf option
in order for conan to generates CMakePresets.json with expected preset names.

See ConanInstall.bat for example commands to run conan install.

## Building

Use CMake presets for configuring and building. Or your IDE directly.

**Currently only known compiler capable of building the project is MSVC from
Visual Studio 17.5**
