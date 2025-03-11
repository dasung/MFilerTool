# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -g -pthread 


# Directories
SRC_DIR := src
COMMON_DIR := common
BUILD_DIR := build
BIN_DIR := bin

# Files
PCH_HEADER := $(COMMON_DIR)/pch.H
PCH_OUTPUT := $(BUILD_DIR)/pch.H.gch

SOURCES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(COMMON_DIR)/*.cpp)
OBJECTS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SOURCES)))
EXECUTABLE := $(BIN_DIR)/MFilerTool

# Ensure directories exist
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Default target
all: $(EXECUTABLE)

# rule for precompiled header
$(PCH_OUTPUT): $(PCH_HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# rules to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(PCH_OUTPUT)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(COMMON_DIR)/%.cpp $(PCH_OUTPUT)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Force PCH usage globally
CXXFLAGS += -include $(COMMON_DIR)/pch.H

# Linker to create executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.gch $(EXECUTABLE) $(BIN_DIR)/*.csv $(BIN_DIR)/devDebug.log 