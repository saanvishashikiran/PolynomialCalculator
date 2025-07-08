# Polynomial Calculator

A C++ program that performs arithmetic and structural operations on single-variable polynomials using pointers and linked lists. This calculator supports addition, subtraction, multiplication, exponentiation, modulus, evaluation, and formatted printing of polynomials. Designed for efficient manipulation of sparse polynomials.

---

## Features

- Singly linked list representation of polynomials using raw pointers
- Zero-coefficient terms are excluded from storage
- Supports:
  - `+`, `-`, `*` arithmetic operations
  - Exponentiation by positive integers
  - Modulus of one polynomial by another
  - Evaluation at integer values
  - Formatted output of polynomials
- Custom input-driven interface for testing all operations

---

## Polynomial Input Format

Each polynomial is defined by: <int> (<int> <int>)*

- The first `<int>` indicates the number of terms
- Each subsequent pair represents a term: `<coefficient> <exponent>`

### Example:

ARBITRARY 4 -24 5 62 3 -31 1 2 0
Represents the polynomial: -24x^5 + 62x^3 - 31x + 2

## Instructions for compiling and running code:

- Compile by typing "make" into the command line and hitting enter
- Run code by typing "./a.out" into the command line and hitting enter

## Supported Commands

The following commands are available and should be typed on **a single line**, including all required input values:

| Command | Description |
|--------|-------------|
| `ZERO` | Create the zero polynomial |
| `ARBITRARY <int> (<int> <int>)*` | Create a polynomial from the given term list |
| `PRINT <int> (<int> <int>)*` | Output the polynomial in standard format |
| `EVAL <int> (<int> <int>)* <int>` | Evaluate the polynomial at a specific integer value |
| `ADD <poly1> <poly2>` | Add two polynomials |
| `SUB <poly1> <poly2>` | Subtract second polynomial from the first |
| `MULT <poly1> <poly2>` | Multiply two polynomials |
| `EXP <poly> <int>` | Raise a polynomial to the given positive integer exponent |
| `MOD <poly1> <poly2>` | Compute the modulus of the first polynomial by the second |
| `QUIT` | Exit the program |

Note: A `<poly>` is always of the form: <int> (<int> <int>)*

## Example Inputs

```text
ZERO
ARBITRARY 3 5 2 3 1 7 0
PRINT 3 5 2 3 1 7 0
EVAL 3 5 2 3 1 7 0 2
ADD 3 2 2 1 1 4 0 2 1 3 0
SUB 3 1 3 4 1 5 0 2 2 1
MULT 2 1 2 3 0 3 1 2 2
EXP 2 1 1 2 0 3
MOD 3 2 3 1 2 4 0 2 1 1
QUIT




