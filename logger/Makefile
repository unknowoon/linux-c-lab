CC = gcc
CFLAGS = -Wall -Wextra -g -pthread -Iinc
LIBDIR = libsrc
SRCDIR = src
INCDIR = inc
BUILDDIR = build

# Library
LIBNAME = liblogger.a
LIBSRC = $(LIBDIR)/logger.c
LIBOBJ = $(BUILDDIR)/logger.o

# Executables
TEST_TARGET = test_logger
MAIN_TARGET = main
TEST_SRC = $(SRCDIR)/test_logger.c
MAIN_SRC = $(SRCDIR)/main.c
TEST_OBJ = $(BUILDDIR)/test_logger.o
MAIN_OBJ = $(BUILDDIR)/main.o

all: $(LIBNAME) $(TEST_TARGET) $(MAIN_TARGET)

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
	rm -rf $(BUILDDIR) $(LIBNAME) $(TEST_TARGET) $(MAIN_TARGET) *.log

# Run test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run main
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Install library (copy to system)
install: $(LIBNAME)
	@echo "Library ready: $(LIBNAME)"
	@echo "Header available: $(INCDIR)/logger.h"

.PHONY: all clean test run install