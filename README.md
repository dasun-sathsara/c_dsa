# Algorithms and Data Structures in C

Welcome to my repository of Algorithms and Data Structures implemented in C. This repository is a personal project aimed at exploring and understanding the intricacies of various Data Structures and Algorithms.

## Structure of the Repository

The repository is organized into two main directories:

- `src`: This directory contains the source code for each algorithm and data structure.
- `tests`: This directory contains the test cases for each implementation in the 'src' directory.

## **Unit Testing with Criterion Framework**

This repository utilizes the **Criterion** framework for unit testing. Below are the steps to run the test cases.

### **Installation**

To get started, you'll need to install the **Criterion** library. You can find detailed installation instructions [here](https://github.com/Snaipe/Criterion).

### **Running Test Cases**

1. **Compile Source Files**:
    
    Before running the test cases, compile the source files into object files. As an example, let's consider compiling the **`arraylist.c`** source file:
    
    ```bash
    gcc -g -Wall -Isrc -c src/arraylist.c -o obj/arraylist.o
    ```
    
2. **Compile Test Cases**:
    
    Next, compile the test case file into an executable. Ensure you link the necessary object files and the **Criterion** library. Here's a command example:
    
    ```bash
    gcc -g -Wall -Isrc -o tests/bin/test_arraylist tests/test_arraylist.c obj/arraylist.o -lcriterion
    
    ```
    
3. **Run the Executable**:
    
    Now, you can run the executable to execute the test cases. For a detailed and descriptive report, use the `--verbose` flag:
    
    ```bash
    tests/bin/test_arraylist --verbose
    ```
