# Compiler Project 

This repositort contains two compiler projects:
1. FrontEnd 
2. MiddleEnd 


## FrontEnd:

The Frontend project involves the development of a lexer (LEX), parser (Bison), and grammar for the Kaleidoscope programming language.

The goal is to convert Kaleidoscope code (.k files) into LLVM IR code. The project includes:
- A lexer that tokenizes the input Kaleidoscope code.
- A parser that generates an abstract syntax tree (AST) from the token stream.
- A set of grammar rules that define the syntax of the Kaleidoscope language

To compile the FE, from the correct directory launch `make`  
To test the FE, from the test folder launch `make`

## MiddleEnd