from conan import ConanFile
from conan.tools.cmake import cmake_layout

class MyProjectConan(ConanFile):

    # define which settings affect the build and dependencies
    settings = "os", "compiler", "build_type", "arch" 

    # specify which Conan generators to use to integrate dependencies with CMake
    # CMakeDeps -> generates CMake config files for dependencies
    # CMakeToolchain -> generates a toolchain file for CMake with compiler and flags
    generators = "CMakeDeps", "CMakeToolchain"

    # define the project layout; here we use the standard CMake directory structure
    def layout(self):
        cmake_layout(self)

    # declare google test dependency
    def requirements(self):
        self.requires("gtest/1.14.0")
