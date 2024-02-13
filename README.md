# Simple Python Compiler For A Princple of Compiler Design Course
## Overview
This is a simple compiler project designed to translate a source code written in a custom programming language into machine code or an intermediate representation. The goal of this compiler is to demonstrate the basic concepts of lexical analysis, syntax analysis, semantic analysis, and code generation.

# Features
Lexical Analysis: Tokenizes the input source code into a sequence of tokens.
Syntax Analysis: Parses the token sequence using backtracking.
Semantic Analysis: Performs basic semantic checks to ensure the correctness of the source code.
Code Generation: Translates the AST into machine code or an intermediate representation.

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
