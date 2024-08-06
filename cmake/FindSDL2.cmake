# FindSDL2.cmake

# Define SDL2 include directory and libraries relative to the project
set(SDL2_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include/SDL2")
set(SDL2_LIBRARIES "${CMAKE_SOURCE_DIR}/libs/SDL2/libSDL2.a" "${CMAKE_SOURCE_DIR}/libs/SDL2/libSDL2main.a")

# Ensure the variables are set correctly
find_path(SDL2_INCLUDE_DIR SDL.h PATHS ${SDL2_INCLUDE_DIRS})
find_library(SDL2_LIBRARY SDL2 PATHS "${CMAKE_SOURCE_DIR}/libs/SDL2")

if(NOT SDL2_LIBRARY)
    message(FATAL_ERROR "SDL2 library not found in ${CMAKE_SOURCE_DIR}/libs/SDL2.")
endif()

set(SDL2_LIBRARIES ${SDL2_LIBRARY} "${CMAKE_SOURCE_DIR}/libs/SDL2/libSDL2main.a")