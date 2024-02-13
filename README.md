# Simple Python Compiler For A Princple of Compiler Design Course
## Overview
This is a simple compiler project designed to translate a source code written in a custom programming language into machine code or an intermediate representation. The goal of this compiler is to demonstrate the basic concepts of lexical analysis, syntax analysis, semantic analysis, and code generation.

# Features
Lexical Analysis: Tokenizes the input source code into a sequence of tokens.
Syntax Analysis: Parses the token sequence using backtracking.
Semantic Analysis: Performs basic semantic checks to ensure the correctness of the source code.
Code Generation: Translates the AST into machine code or an intermediate representation.

# Custom Programming Language Features
The custom programming language is a simple language that supports the following features:
- Arithmetic operations: addition, subtraction, multiplication, division and modulo
- Variable declaration and assignment for integers, floats, bool and strings
- Logical operations: and, or, not
- Comparison operations: equal, not equal, greater than, less than, greater than or equal, less than or equal
- String concatenation

# Prerequisites
Before using the compiler, ensure you have the following installed:
C/C++ compiler

# Usage
To compile the source code, run the following command:
```bash
g++ main.cpp -o compiler
```
To run the compiler, use the following command:
```bash
./compiler <source_file>
```

# Example
The following is an example of a source code written in the custom programming language:
```bash
g++ main.cpp -o compiler
./compiler test-0.py
```
