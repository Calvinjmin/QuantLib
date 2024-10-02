#!/bin/bash

# Navigate to the build directory
cd build || { echo "Build directory not found."; exit 1; }

# Remove all files in the build directory
rm -rf *

# Run CMake to configure the project
cmake .. -G "Unix Makefiles"

# Build the project
make