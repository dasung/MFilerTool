# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g

# Directories
BUILD_DIR := build
BIN_DIR := bin
SRC_DIR := src
COMMON_DIR := common
BIN := $(BIN_DIR)/MFilerTool

# Sources and Objects
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Include directory
INCLUDES := -I$(COMMON_DIR)

# Rules
$(BIN): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BIN)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/* $(BIN) 
