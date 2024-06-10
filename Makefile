# Compiler
CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++14

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES_NO_MAIN = $(filter-out $(SRC_DIR)/main.cpp, $(SRC_FILES))
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJ_FILES_NO_MAIN = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES_NO_MAIN))
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_FILES))

# Executable
EXEC = $(BIN_DIR)/MiniCompressor
TEST_EXEC = $(BIN_DIR)/MiniCompressorTest

# Create directories if they do not exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target
all: $(EXEC) $(TEST_EXEC)

# Build executable
$(EXEC): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@

# Build test executable
$(TEST_EXEC): $(OBJ_FILES_NO_MAIN) $(TEST_OBJ_FILES)
	$(CXX) $(OBJ_FILES_NO_MAIN) $(TEST_OBJ_FILES) -lgtest -lgtest_main -pthread -o $@

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*

.PHONY: all clean
