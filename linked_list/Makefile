CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
INCDIR = .
BUILDDIR = build

# Library
LIBNAME = liblinked_list.a
LIBSRC = linked_list.c
LIBOBJ = $(BUILDDIR)/linked_list.o

# Executable
TARGET = main
SRC = main.c
OBJ = $(BUILDDIR)/main.o

all: $(LIBNAME) $(TARGET)

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Build library
$(LIBNAME): $(LIBOBJ)
	ar rcs $(LIBNAME) $(LIBOBJ)

$(LIBOBJ): $(LIBSRC) linked_list.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $(LIBSRC) -o $(LIBOBJ)

# Build main executable
$(TARGET): $(OBJ) $(LIBNAME)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -L. -llinked_list

$(OBJ): $(SRC) linked_list.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $(SRC) -o $(OBJ)

# Run program
run: $(TARGET)
	./$(TARGET)

# Test target
test: $(TARGET)
	@echo "Running linked_list test..."
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILDDIR) $(LIBNAME) $(TARGET)

# Install library
install: $(LIBNAME)
	@echo "Library ready: $(LIBNAME)"
	@echo "Header available: linked_list.h"

.PHONY: all run test clean install