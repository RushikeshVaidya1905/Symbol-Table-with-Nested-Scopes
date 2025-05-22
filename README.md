# Symbol-Table-with-Nested-Scopes

## Project Description

This project implements a **symbol table** with support for **nested scopes**, which is a crucial component of a compiler. The symbol table allows for variable declaration and lookup across different scopes, mimicking the way modern programming languages handle block-level variable visibility.

The core structure is based on **hash tables**, with each scope represented by a separate hash table. Scopes are linked together, forming a chain of environments where lookup operations can traverse up to find the appropriate variable definitions.

---

## Objectives

- Create a symbol table data structure with nested scope handling.
- Support operations such as:
  - `begin`: Start a new scope.
  - `assign var value`: Insert or update a variable in the current scope.
  - `print var`: Lookup the value of a variable starting from the current scope upwards.
  - `end`: Close the current scope and return to the enclosing one.

---

## Features

- Dynamic scope management using linked hash tables.
- First-found rule for variable lookup (innermost scope first).
- Efficient insertion and lookup using hashing.
- Scope begin and end handling with proper linkage.

---
