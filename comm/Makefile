CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c99 -g -pthread
CXXFLAGS = -Wall -Wextra -std=c++17 -g -pthread
SRCDIR = src
INCDIR = inc
OBJDIR = obj
BINDIR = bin
TESTDIR = tests
LOGGERDIR = ../logger
LOGGERLIB = $(LOGGERDIR)/liblogger.a

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(OBJDIR)/%.o)

TARGETS = commManager comm
TEST_TARGET = test_runner

.PHONY: all clean test

all: $(TARGETS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(OBJDIR)/Comm.o $(LOGGERLIB) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LOGGERLIB) -lgtest -lgtest_main -pthread

commManager: $(OBJDIR)/commManager.o $(LOGGERLIB) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $< $(LOGGERLIB)

comm: $(OBJDIR)/Comm.o $(LOGGERLIB) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $< $(LOGGERLIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LOGGERDIR)/inc -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -I$(LOGGERDIR)/inc -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(TARGETS) $(TEST_TARGET) *.log

install: all
	@echo "Built targets: $(TARGETS)"
	@echo "Usage:"
	@echo "  ./commManager [port]  - Start server (default port: 8080)"
	@echo "  ./comm <socket_fd>    - Handle client communication (called by commManager)"

.SUFFIXES:
.SUFFIXES: .c .o