#!/bin/bash

# Create the build directory if it doesn't exist
mkdir -p build



# clean the project
echo "cleaning MFilerTool..."
make clean

# Build the project
echo "making MFilerTool..."
make

cd bin
# Run the executable with --no-window argument
echo "runing MFilerTool in silent mode..."
./MFilerTool --no-window

cd ..
echo "done!"