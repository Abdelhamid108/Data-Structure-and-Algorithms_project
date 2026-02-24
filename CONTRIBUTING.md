# Contributing Guide

## Development workflow
1. Create a feature branch from `main`.
2. Build and run tests locally.
3. Ensure formatting and naming are consistent.
4. Open a pull request with a clear summary and test evidence.

## Build
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Coding guidelines
- Use C++17 or newer.
- Prefer RAII and standard library containers over raw pointers.
- Keep I/O handling separate from core business logic when possible.
- Document public classes and non-trivial methods.
