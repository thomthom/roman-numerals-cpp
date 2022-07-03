cmake_minimum_required(VERSION 3.16)

# https://cliutils.gitlab.io/modern-cmake/chapters/basics.html

# Determine if the project is built as a subproject (using add_subdirectory)
# or if it is the master project.
# https://github.com/fmtlib/fmt/blob/8c8f74a870bbf2d9de726bc347d05831cdc01da7/CMakeLists.txt#L12
set(MASTER_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT ON)
  message(STATUS "CMake version: ${CMAKE_VERSION}")
endif()

option(ROMAN_NUMERAL_TEST "Generate the test targets." ${MASTER_PROJECT})

# Set the default C++ standard when building as master project.
if(MASTER_PROJECT)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
  # Set CMAKE_CXX_EXTENSIONS to OFF so we get -std=c++11 instead of gnu++11.
endif()

project(RomanNumerals
  VERSION 1.0.0
  DESCRIPTION "Roman Numeral type for C++"
  LANGUAGES C CXX
)

# Enable MSVC multiple processes compilation. (Visual Solution/MSBuild)
# https://blog.kitware.com/cmake-building-with-all-your-cores/
# https://stackoverflow.com/questions/10688549/how-do-i-configure-portable-parallel-builds-in-cmake
if(MASTER_PROJECT AND MSVC)
  # Enable Build with Multiple Processes.
  add_compile_options(/MP)
endif()

# Specify the list of directories to search for cmake modules.
# https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
list(PREPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_subdirectory("src")

# Testing
include(CTest)
if(ROMAN_NUMERAL_TEST AND BUILD_TESTING)
  message(STATUS "Testing enabled")
  enable_testing()
  add_subdirectory("tests")
endif()
