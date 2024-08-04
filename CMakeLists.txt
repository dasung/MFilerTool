# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Donga VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)              # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED True)   # Enforce the standard

# Specify output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the executable
add_executable(Donga src/main.cpp)