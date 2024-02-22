# Variables
CC = gcc
CFLAGS = -g -Wall -Isrc
OBJDIR = obj
BINDIR = tests/bin
CRITERION = -lcriterion
# SOURCES = $(wildcard src/*.c)
SOURCES = src/doubly_linked_list.c
OBJECTS = $(SOURCES:src/%.c=$(OBJDIR)/%.o)
# TEST_SOURCES = $(wildcard tests/*.c)
TEST_SOURCES = tests/test_doubly_linked_list.c
TESTS = $(TEST_SOURCES:tests/%.c=$(BINDIR)/%)

# Default rule
all: $(OBJECTS) $(TESTS)

# Rule for creating object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule for creating binary directory
$(BINDIR):
	mkdir -p $(BINDIR)

# Rule for compiling source files into object files
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling test cases and linking with the Criterion library
$(BINDIR)/%: tests/%.c $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $< $(OBJECTS) $(CRITERION)

# Custom rule to run a test binary
test_%: $(BINDIR)/test_%
	$<

# Rule to clean up the generated files
clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/*

.PHONY: all clean
