# FindSDL2.cmake

# Define the SDL2 include directory and library directories relative to the project
set(SDL2_INCLUDE_DIRS "C:/SDL2-2.30.6/x86_64-w64-mingw32/include/SDL2")

# Find the SDL2 header files
find_path(SDL2_INCLUDE_DIR SDL.h PATHS ${SDL2_INCLUDE_DIRS})

# Find the SDL2 libraries
find_library(SDL2_LIBRARY SDL2.dll PATHS "C:/SDL2-2.30.6/x86_64-w64-mingw32/lib")
find_library(SDL2MAIN_LIBRARY SDL2main PATHS "C:/SDL2-2.30.6/x86_64-w64-mingw32/lib")

if(NOT SDL2_LIBRARY OR NOT SDL2MAIN_LIBRARY)
    message(FATAL_ERROR "SDL2 libraries not found in C:/SDL2-2.30.6/x86_64-w64-mingw32/lib.")
endif()

# Set the libraries in the correct order
set(SDL2_LIBRARIES "${SDL2MAIN_LIBRARY}" "${SDL2_LIBRARY}")