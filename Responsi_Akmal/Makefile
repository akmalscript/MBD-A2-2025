CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = btree_demo
TEST_TARGET = btree_test

# Source files
MAIN_SOURCES = main.cpp Node.cpp BTree.cpp
TEST_SOURCES = test_btree.cpp Node.cpp BTree.cpp
LIB_SOURCES = Node.cpp BTree.cpp

# Object files
MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
LIB_OBJECTS = $(LIB_SOURCES:.cpp=.o)

# Header files
HEADERS = Node.h BTree.h BTreeConfig.h

.PHONY: all clean test run run-test debug release lib install

# Default target
all: $(TARGET)

# Main demo program
$(TARGET): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test suite
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Static library (future enhancement)
lib: libbtree.a

libbtree.a: $(LIB_OBJECTS)
	ar rcs $@ $^

# Compile object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean all build artifacts
clean:
	rm -f *.o $(TARGET) $(TEST_TARGET) libbtree.a

# Run main demo
run: $(TARGET)
	./$(TARGET)

# Run test suite
test: $(TEST_TARGET)
	./$(TEST_TARGET)

run-test: test

# Debug build
debug: CXXFLAGS += -g -DDEBUG -O0
debug: clean $(TARGET) $(TEST_TARGET)

# Release build (optimized)
release: CXXFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)

# Profile build
profile: CXXFLAGS += -pg -O2
profile: clean $(TARGET)

# Address sanitizer build
sanitize: CXXFLAGS += -fsanitize=address -g -O1
sanitize: clean $(TARGET) $(TEST_TARGET)

# Memory leak detection
valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Code coverage (requires gcov)
coverage: CXXFLAGS += --coverage -O0 -g
coverage: clean $(TEST_TARGET)
	./$(TEST_TARGET)
	gcov $(TEST_SOURCES)

# Install headers (basic implementation)
install: $(HEADERS)
	mkdir -p /usr/local/include/btree
	cp $(HEADERS) /usr/local/include/btree/

# Benchmark (future enhancement)
benchmark: release
	time ./$(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build main demo (default)"
	@echo "  test      - Build and run test suite"
	@echo "  lib       - Build static library"
	@echo "  debug     - Debug build with symbols"
	@echo "  release   - Optimized release build"
	@echo "  sanitize  - Build with address sanitizer"
	@echo "  valgrind  - Run with valgrind memory checker"
	@echo "  coverage  - Generate code coverage report"
	@echo "  clean     - Remove all build artifacts"
	@echo "  run       - Build and run demo"
	@echo "  install   - Install headers to system"
	@echo "  help      - Show this help message"

.SUFFIXES: .cpp .o
