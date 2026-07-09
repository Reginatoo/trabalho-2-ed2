CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -g
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = ../ted

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean