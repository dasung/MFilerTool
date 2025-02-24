#!/bin/bash

# Create the build directory if it doesn't exist
mkdir -p build

# Navigate into the build directory
cd build

# Run CMake to configure the project
echo "cmaking MFilerTool..."
cmake ..

# Build the project using Ninja
echo "making MFilerTool..."
ninja

cd ../bin
# Run the executable with --no-window argument
echo "runing MFilerTool in silent mode..."
./MFilerTool.exe --no-window
#./MFilerTool.exe

cd ..
echo "done!"