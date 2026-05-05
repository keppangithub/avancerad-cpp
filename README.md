# Avancerad C++ – Lab 1: Vector

A custom implementation of a dynamic array (`std::vector`) in C++, built as part of an advanced C++ university course.

## What's implemented

The `Vector<T>` template class covers:

- **Rule of Five**: default, copy, and move constructors; copy and move assignment; destructor
- **Iterators**: forward, reverse, and const variants (`begin`, `end`, `cbegin`, `rbegin`, etc.)
- **Capacity management**: `push_back`, `pop_back`, `resize`, `reserve`, `shrink_to_fit`
- **Element access**: `operator[]`, `at()` with bounds checking, `data()`
- **Comparison operators**: `==`, `!=`, `<`, `>`, `<=`, `>=` (lexicographic)
- **Stream output**: `operator<<`
- **Invariant checking**: `Invariant()` asserted on mutating operations

## Usage

```cpp
Vector<int> v;
v.push_back(1);
v.push_back(2);
v.push_back(3);

for (auto x : v) std::cout << x << " ";  // 1 2 3

Vector<char> s("hello");
std::cout << s;  // hello
```

## Build

Single file, no build system needed:

```bash
g++ -std=c++20 Lab1/Vector.cpp -o vector
./vector
```
