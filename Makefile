CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinit
SRCS = $(wildcard *.c) $(wildcard init/*.c) $(wildcard feat/flags/*.c)
TARGET = .build/main

all:
	mkdir -p .build
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
	./.build/main tests/programs/test.c -fd

clean:
	rm -rf .build
