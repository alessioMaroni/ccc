.PHONY: all

BUILD_DIR = .build

all:
	mkdir -p .build

	gcc main.c -o $(BUILD_DIR)/main

	./$(BUILD_DIR)/main tests/basic-program.c
