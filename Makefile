CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = compiler
SRC = src/main.c \
	src/file_reader.c \
	src/lexer.c
OBJ = $(SRC:.c=.o)

TEST_SRC = src/test_lexer.c \
	src/lexer.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = test_lexer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test
