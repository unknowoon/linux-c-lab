CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -g -pthread -Iinc
CXXFLAGS = -Wall -Wextra -g -pthread -Iinc -std=c++17
LIBDIR = libsrc
SRCDIR = src
INCDIR = inc
TESTDIR = tests
BUILDDIR = build

# Library
LIBNAME = liblogger.a
LIBSRC = $(LIBDIR)/logger.c
LIBOBJ = $(BUILDDIR)/logger.o

# Executables
TEST_TARGET = test_logger
MAIN_TARGET = main
GTEST_TARGET = gtest_logger
TEST_SRC = $(SRCDIR)/test_logger.c
MAIN_SRC = $(SRCDIR)/main.c
GTEST_SRC = $(TESTDIR)/test_logger.cpp
TEST_OBJ = $(BUILDDIR)/test_logger.o
MAIN_OBJ = $(BUILDDIR)/main.o
GTEST_OBJ = $(BUILDDIR)/test_logger_gtest.o

# Google Test 플래그 (pkg-config로 자동 감지)
GTEST_CFLAGS = $(shell pkg-config --cflags gtest 2>/dev/null || echo "-I/opt/homebrew/include")
GTEST_LIBS = $(shell pkg-config --libs gtest 2>/dev/null || echo "-L/opt/homebrew/lib -lgtest -lgtest_main")

all: $(LIBNAME) $(TEST_TARGET) $(MAIN_TARGET)

gtest: $(GTEST_TARGET)

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Build library
$(LIBNAME): $(LIBOBJ)
	ar rcs $(LIBNAME) $(LIBOBJ)

$(LIBOBJ): $(LIBSRC) $(INCDIR)/logger.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(LIBSRC) -o $(LIBOBJ)

# Build test executable
$(TEST_TARGET): $(TEST_OBJ) $(LIBNAME)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) -L. -llogger

$(TEST_OBJ): $(TEST_SRC) $(INCDIR)/logger.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

# Build main executable
$(MAIN_TARGET): $(MAIN_OBJ) $(LIBNAME)
	$(CC) $(CFLAGS) -o $(MAIN_TARGET) $(MAIN_OBJ) -L. -llogger

$(MAIN_OBJ): $(MAIN_SRC) $(INCDIR)/logger.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

# Clean build artifacts
clean:
	rm -rf $(BUILDDIR) $(LIBNAME) $(TEST_TARGET) $(MAIN_TARGET) $(GTEST_TARGET) *.log

# Run test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Build Google Test executable
$(GTEST_TARGET): $(GTEST_OBJ) $(LIBOBJ)
	$(CXX) $(CXXFLAGS) -o $(GTEST_TARGET) $(GTEST_OBJ) $(LIBOBJ) $(GTEST_LIBS)

$(GTEST_OBJ): $(GTEST_SRC) $(INCDIR)/logger.h | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(GTEST_CFLAGS) -c $(GTEST_SRC) -o $(GTEST_OBJ)

# Run main
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Run Google Test
run_gtest: $(GTEST_TARGET)
	./$(GTEST_TARGET)

# Install library (copy to system)
install: $(LIBNAME)
	@echo "Library ready: $(LIBNAME)"
	@echo "Header available: $(INCDIR)/logger.h"

.PHONY: all gtest clean test run run_gtest install