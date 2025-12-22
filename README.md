# C4

A minimal programming language that transpiles to C. Hobby project for learning compiler design and is not intended to replace C.

## Current Features

**Working:**
- Integer variables with `:=` assignment
- Arithmetic operators: `+`, `-`, `*`, `/` with proper precedence
- Comparison operators: `<`, `>`, `==`, `!=`, `<=`, `>=`
- Parentheses for grouping
- `print()` statement
- Full lexer → parser → code generator pipeline

**Example:**
```c4
x := 5 + 10;
y := x * 2;
result := y > 15;
print(result);
```

Generates valid C code, compiles, and runs.

**What's Missing** \
- 	Control flow (if/else, while loops)
- Functions
- Types beyond integers
- Strings

## Build and run
```bash
make
./transpiler tests/comparisons.c4
./program
```
