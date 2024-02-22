# Define the source files
SOURCES = src/arraylist.c src/doubly_linked_list.c src/hash_table.c src/hashing_functions.c

# Define the test file
TEST_FILE = tests/test_hash_table.c

# ---------------------------------------------------------------------------

# Define the object directory
OBJ_DIR = obj

# Define the test binary directory and executable name
TEST_BIN_DIR = tests/bin

TEST_EXEC = $(TEST_BIN_DIR)/$(notdir $(TEST_FILE:.c=))

# Define the compiler
CC = gcc

# Define the compiler flags
CFLAGS = -g -Wall -Isrc

# Convert the .c filenames to .o to give a list of object files to build
OBJS = $(SOURCES:src/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(OBJS)

# Rule for creating the object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule for converting .c files in SRC to .o files in OBJ_DIR
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling the test file and linking with the object files
tests: $(OBJS)
	mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_FILE) $(OBJS) -lcriterion

# Rule to run the test binary
runtests: tests
	./$(TEST_EXEC)

# Rule to check for memory leaks
memcheck: tests
	valgrind --leak-check=full ./$(TEST_EXEC)

# Additional rules for cleaning up the project
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TEST_BIN_DIR)/*

.PHONY: all tests runtests memcheck clean
