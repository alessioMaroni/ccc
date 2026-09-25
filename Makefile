.PHONY: all

BUILD_DIR = .build

all:
	mkdir -p .build

	gcc main.c include/lexer.c include/codegen.c -o $(BUILD_DIR)/main

	./$(BUILD_DIR)/main tests/basic-program.c
