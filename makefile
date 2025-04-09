CC = gcc
CFLAGS = -Wall -g -I./include
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin/bfx86

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(BIN)
