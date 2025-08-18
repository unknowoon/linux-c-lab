CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
INCDIR = .
BUILDDIR = build

# Library
LIBNAME = libmy_string.a
LIBSRCS = my_memchr.c my_memcmp.c my_memcpy.c my_memmove.c my_memset.c \
          my_strcat.c my_strchr.c my_strcmp.c my_strcpy.c my_strcspn.c \
          my_strlen.c my_strncmp.c my_strncpy.c my_strpbrk.c my_strrchr.c \
          my_strspn.c my_strstr.c my_strtok.c
LIBOBJS = $(LIBSRCS:%.c=$(BUILDDIR)/%.o)

all: $(LIBNAME)

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Build library
$(LIBNAME): $(LIBOBJS)
	ar rcs $(LIBNAME) $(LIBOBJS)

$(BUILDDIR)/%.o: %.c my_string.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILDDIR) $(LIBNAME)

# Test target (placeholder)
test:
	@echo "No tests defined for my_string library"

# Install library
install: $(LIBNAME)
	@echo "Library ready: $(LIBNAME)"
	@echo "Header available: my_string.h"

.PHONY: all clean test install