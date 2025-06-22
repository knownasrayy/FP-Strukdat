CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./include
BUILD_DIR = build
TEST_BIN_DIR = test_bin

# Source files (excluding main.cpp)
SRCS = $(wildcard src/**/*.cpp)
OBJS = $(SRCS:src/%.cpp=$(BUILD_DIR)/%.o)

# Main executable
MAIN_SRC = main.cpp
MAIN_OBJ = $(BUILD_DIR)/main.o
TARGET = main

# Test files
TEST_SRCS = $(wildcard test/*.cpp)
TEST_BINS = $(patsubst test/%.cpp,$(TEST_BIN_DIR)/%,$(TEST_SRCS))

# Test flags
TEST_LIBS =

# Default target
all: $(TARGET)

# Main program
$(TARGET): $(OBJS) $(MAIN_OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) $(MAIN_OBJ) -o $@

# Compile source files
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main file
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build tests
$(TEST_BIN_DIR)/%: test/%.cpp $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< $(OBJS) $(TEST_LIBS) -o $@

# Run single test
test_%: $(TEST_BIN_DIR)/%
	./$<

# Run all tests
.PHONY: test
test: $(TEST_BINS)
	@echo "Running all tests..."
	@for test in $(TEST_BINS); do \
		echo "\nRunning $$test..."; \
		./$$test || exit 1; \
	done
	@echo "\nAll tests passed!"

# Clean build files
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEST_BIN_DIR) $(TARGET)

# Build and run
.PHONY: run
run: $(TARGET)
	./$(TARGET)