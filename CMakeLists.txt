
# CMakefile.txt: CMakeLists.txt
# Project: Template
# Date: 2021
# Author: (AS) Alexander Sacharov <a.sacharov@gmx.de> (alexander)
#
# Notes:

cmake_minimum_required(VERSION 3.5)

# Set project name
project(TEMPLATE-CMAKE-LIB)

# build switches
option(BUILD_TESTING "Build tests programs" ON)
option(BUILD_EXAMPLES "Build samples applications" ON)
option(BUILD_DOC "Build documentation" OFF)
option(RUN_CPPCHECK "Run cppcheck with build" OFF)

# Export compile_commads.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify C + CXX Standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Some options for the compiler
add_compile_options(-Wall -Wextra -Werror=return-type -Wpedantic)

# Build debug-configuration
set(CMAKE_BUILD_TYPE Debug)

# Prepare for conan
set(CONAN_DISABLE_CHECK_COMPILER ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Install at cwd
set(CMAKE_INSTALL_PREFIX ./dist)

#
# run check
#
if (RUN_CPPCHECK)
    set(CMAKE_C_CPPCHECK "cppcheck")
    list(APPEND CMAKE_C_CPPCHECK
            "--enable=style,warning,performance,portability"
            "--std=c11"
            "--quiet")

    set(CMAKE_CXX_CPPCHECK "cppcheck")
    list(APPEND CMAKE_CXX_CPPCHECK
            "--enable=style,warning,performance,portability"
            "--std=c++11"
            "--std=c++11"
            "--quiet"
            "--suppress=*:*.conan*"
            "--suppress=*:*submodules*")
endif ()

#
# Add all artefacts
#
add_subdirectory(lib)

# Build samples applications
if (BUILD_TESTING)
    # Enable testing for the project
    add_subdirectory(tests)
endif ()

# Build samples applications
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

# Build documentation
if (BUILD_DOC)
    add_subdirectory(docs)
endif ()
