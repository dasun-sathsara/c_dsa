CC=gcc
CFLAGS=-g -Wall -I$(SRC_DIR)
SRC_DIR=src
TEST_DIR=tests
BIN_DIR=bin
OBJ_DIR=obj
TEST_BIN_DIR=$(TEST_DIR)/bin

# Create bin and obj directories if they don't exist
$(shell mkdir -p $(BIN_DIR))
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(TEST_BIN_DIR))

# Collect all .c files in SRC_DIR and TEST_DIR
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
TEST_FILES=$(wildcard $(TEST_DIR)/*.c)

# Replace .c with .o and prepend OBJ_DIR/ to each filename
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

EXECUTABLE=main

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(EXECUTABLE) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $< $(OBJ_FILES)

tests: $(patsubst $(TEST_DIR)/%.c,$(TEST_BIN_DIR)/%,$(TEST_FILES))

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(EXECUTABLE) $(TEST_BIN_DIR)/*
