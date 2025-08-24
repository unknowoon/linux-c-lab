CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -pthread
SRCDIR = src
INCDIR = inc
OBJDIR = obj
BINDIR = bin
LOGGERDIR = ../logger
LOGGERLIB = $(LOGGERDIR)/liblogger.a

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGETS = CommManager comm

.PHONY: all clean

all: $(TARGETS)

CommManager: $(OBJDIR)/CommManager.o $(LOGGERLIB) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $< $(LOGGERLIB)

comm: $(OBJDIR)/Comm.o $(LOGGERLIB) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $< $(LOGGERLIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LOGGERDIR)/inc -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(TARGETS) *.log

install: all
	@echo "Built targets: $(TARGETS)"
	@echo "Usage:"
	@echo "  ./CommManager [port]  - Start server (default port: 8080)"
	@echo "  ./comm <socket_fd>    - Handle client communication (called by CommManager)"

.SUFFIXES:
.SUFFIXES: .c .o