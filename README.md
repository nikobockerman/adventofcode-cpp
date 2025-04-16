# Advent Of Code problem solutions with C++

[![CI](https://github.com/nikobockerman/adventofcode-cpp/actions/workflows/ci.yml/badge.svg)](https://github.com/nikobockerman/adventofcode-cpp/actions/workflows/ci.yml)

## The repository

This repository contains solutions to some of the Advent Of Code problems
implemented in C++. This repository also serves a purpose of learning about new
C++ features and utilizing those in the solutions.

## Instructions for building

This project has some dependencies to other packages. Those dependencies are
managed using `conan`. You should first install dependencies with
`conan install` and then use CMake presets based on what conan generates.

### Installing dependencies

Use Conan to install dependencies using a profile which you have available.

Example using default profile:

```shell
$ conan install --build=missing .
```

### Building

Use CMake presets for configuring and building. Conan install automatically
generates CMake Presets and includes them in CMakeUserPresets.json. Conan
generates CMake Presets for configuring, building and testing.

List available configuration presets with `cmake --list-presets` and configure
one of them with `cmake --preset <name>`. Use `cmake --build --preset <name>`
for building.

CMakeUserPresets.json file is meant for configuring CMake Presets that are
suitable for individual developers. The CMakePresets.json file in the repository
contains few useful configuration presets that you may choose to inherit in your
own presets.
