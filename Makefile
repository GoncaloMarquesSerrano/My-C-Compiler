CC = gcc
CFLAGS = -Wall -Wextra -g -Wpedantic
TARGET = compiler
SRC = src/main.c \
	src/file_reader/file_reader.c \
	src/lexer/lexer.c \
	src/parser/parser.c \
	src/ast/ast.c \
	src/token/token.c \
	src/assembly/assembly.c 
OBJ = $(SRC:.c=.o)

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
