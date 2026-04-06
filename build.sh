#!/bin/bash

# Configuration
BUILD_DIR="build"
EXECUTABLE_NAME="MagicPixelEngine"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${GREEN}== Starting MagicPixelEngine Build Process ==${NC}"

# Initialize submodules if necessary
if [ -d ".git" ]; then
    echo "Initializing submodules..."
    git submodule update --init --recursive
fi

# Check for brew on macOS
if [[ "$OSTYPE" == "darwin"* ]]; then
    if ! command -v brew &> /dev/null; then
        echo -e "${RED}Error: Homebrew is not installed. Please install it from https://brew.sh/${NC}"
        exit 1
    fi
    
    # Check for library dependencies
    echo "Checking dependencies..."
    pkgs=("sdl2" "sdl2_image" "sdl2_ttf" "cmake")
    for pkg in "${pkgs[@]}"; do
        if ! brew list $pkg &>/dev/null; then
            echo -e "Installing $pkg..."
            brew install $pkg
        fi
    done
fi

# Create build directory
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# Run CMake
echo -e "${GREEN}Configuring with CMake...${NC}"
cmake ..

# Compile
echo -e "${GREEN}Compiling...${NC}"
# Use all available cores for faster compilation
if [[ "$OSTYPE" == "darwin"* ]]; then
    make -j$(sysctl -n hw.ncpu)
else
    make -j$(nproc)
fi

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Build successful!${NC}"
    echo -e "Run the engine with: ./${BUILD_DIR}/app/${EXECUTABLE_NAME}"
else
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi
