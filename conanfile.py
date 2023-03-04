from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class AdventOfCodeCppRecipe(ConanFile):
    name = "adventofcodecpp"
    version = "1.0"
    package_type = "application"

    # Optional metadata
    license = "MIT"
    author = "Niko Böckerman <git.585wj@slmail.me>"
    url = "https://github.com/nikobockerman/adventofcode-cpp"
    description = "Advent Of Code problem solutions with C++"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "2022/*", "common/*", "input.in.hpp"

    def requirements(self):
        self.requires("fmt/[^9.1.0]")
        self.requires("spdlog/[^1.11.0]")
        self.requires("gtest/[^1.12.1]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.user_presets_path = "ConanPresets.json"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
