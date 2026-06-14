<div align="center">

<pre>
╔═════════════════════════════════════════════════════════════════════╗
║                                                                     ║
║   ██████╗███████╗██████╗ ██████╗ ███████╗██████╗ ██╗   ██╗███████╗  ║
║  ██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗██║   ██║██╔════╝  ║
║  ██║     █████╗  ██████╔╝██████╔╝█████╗  ██████╔╝██║   ██║███████╗  ║
║  ██║     ██╔══╝  ██╔══██╗██╔══██╗██╔══╝  ██╔══██╗██║   ██║╚════██║  ║
║  ╚██████╗███████╗██║  ██║██████╔╝███████╗██║  ██║╚██████╔╝███████║  ║
║   ╚═════╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝  ║
║                                                                     ║
╚═════════════════════════════════════════════════════════════════════╝
</pre>

</div>

Cerberus is a custom interpreted programming language built in C++, inspired by the three-headed guardian of the underworld.

The interpreter is structured into three strict stages, each represented by a head of Cerberus:

- **Gatekeeper** - lexical analysis and tokenization
- **Judge** - parsing and abstract syntax tree (AST) construction
- **Executioner** - runtime interpretation and execution

Internally it leans on core data structures and algorithms - a tree for the AST, hash maps for the keyword/operator tables and variable scopes, and recursion for both parsing and evaluation.

## Features

- **Variables** - integer variables declared with `let`, plus reassignment to existing ones
- **Arithmetic & comparison** - `+`, `-`, `*`, `/` and `<`, `>`, `==`
- **Grouping** - parentheses, with operator precedence encoded in the AST
- **Output** - `print(...)` statements
- **Scoping** - block statements `{ ... }` with lexical scoping and shadowing
- **Control flow** - `if` / `else` conditionals and `while` loops
- **Diagnostics** - unknown characters and unexpected tokens reported with their line number

## Architecture

A program flows through the three heads in order, each raising the level of abstraction:

```
source text  ──▶  Gatekeeper  ──▶  tokens  ──▶  Judge  ──▶  AST  ──▶  Executioner  ──▶  output
                    (lexer)                      (parser)             (interpreter)
```

| Component | Path | Responsibility |
| --- | --- | --- |
| Entry point | `main.cpp` | Reads a source file and drives the pipeline |
| Token | `include/token.h` | Token type and `Token` struct |
| Gatekeeper | `src/lexer` | Scans characters into tokens, tracking line numbers |
| AST | `include/ast` | Expression and statement node definitions |
| Judge | `src/parser` | Recursive-descent parser that builds the AST |
| Executioner | `src/interpreter` | Walks the AST and executes statements |
| Environment | `include/interpreter/environment.h` | Variable scopes as a chain of hash maps |

## Quickstart

```bash
# 1. Clone
git clone https://github.com/omanshchoudhary/cerberus.git
cd cerberus

# 2. Build (produces the `cerberus` executable; `make clean` removes it)
make

# 3. Run a program
./cerberus program.cerb
```

A Cerberus program is a plain text file; the `.cerb` extension is a convention and is not enforced.

## Example

The first ten Fibonacci numbers (`fib.cerb`):

```
let a = 0;
let b = 1;
let n = 10;
let i = 0;

while (i < n) {
    print(a);
    let next = a + b;
    a = b;
    b = next;
    i = i + 1;
}
```

```
$ ./cerberus fib.cerb
0
1
1
2
3
5
8
13
21
34
```

## Language Guide

```
let x = 10 + 2 * 3;   // x is 16 - * and / bind tighter than + and -
print(x);

x = x + 1;            // reassignment; assigning an undeclared variable is an error

print(x > 10);        // comparisons evaluate to 1 (true) or 0 (false)

if (x > 10) {         // if / else
    print(1);
} else {
    print(0);
}

let y = 1;            // block scoping
{
    let y = 2;
    print(y);         // prints 2 - inner let shadows the outer y
}
print(y);             // prints 1 - outer y is unchanged
```

Cerberus does not parse comments; the `//` annotations above are for explanation only.

## Tests

A feature harness in `tests/` runs a short program for each language construct and prints the result:

```bash
make test
```
