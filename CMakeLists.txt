# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Donga VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)              # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED True)   # Enforce the standard

# Specify output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the 'cmake' directory to the CMake module search path (for FindSDL2.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Define the source files
set(SOURCES src/main.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Find and link SDL2
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})