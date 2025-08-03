CC = gcc
CFLAGS = -Wall -Wextra -g -pthread
TARGET = test_logger
OBJS = logger.o test_logger.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

logger.o: logger.c logger.h
	$(CC) $(CFLAGS) -c logger.c

test_logger.o: test_logger.c logger.h
	$(CC) $(CFLAGS) -c test_logger.c

clean:
	rm -f $(OBJS) $(TARGET) test.log

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run