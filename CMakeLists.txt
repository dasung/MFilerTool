# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Donga VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)              # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED True)   # Enforce the standard

# Specify output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

# Add the 'cmake' directory to the CMake module search path (for FindSDL2.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Define the source files
set(SOURCES src/main.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# locate the SDL2 library and its components (SDL2.h, libSDL2.a, libSDL2main.a, SDL2_INCLUDE_DIRS, SDL2_LIBRARIES, etc.) 
find_package(SDL2 REQUIRED)

message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")

include_directories(${SDL2_INCLUDE_DIRS})

# apply the linker flag globally to all executables 
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")

# set linker flag only to a specific target (only if really needed)
# set_target_properties(Donga PROPERTIES LINKER_FLAGS "-Wl,-subsystem,windows")

# link against MinGW runtime and SDL2 libraries
target_link_libraries(${PROJECT_NAME} mingw32 ${SDL2_LIBRARIES})