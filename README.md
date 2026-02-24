# Library Management System (C++ Terminal Application)

A professional, interview-ready C++ project that implements a **Library Management System** on top of a **custom Doubly Linked List** data structure.

This repository focuses on clean architecture, robust terminal input handling, predictable memory management, and complete technical documentation.

---

## 1) Project Overview

This project allows users to manage multiple named library lists (up to 5). Inside each list, users can:
- Insert books at the head, tail, or a specific position.
- Delete books from the head, tail, specific position, or by title.
- Search for books by title.
- Update book metadata.
- Traverse and display books in forward or backward order.
- Sort books alphabetically by title.

The system is intentionally terminal-based to emphasize data-structure design, correctness, and algorithmic reasoning.

---

## 2) Architecture and Design Choices

### 2.1 Chosen Architecture
The project follows a **layered modular architecture**:

1. **UI Layer** (`main.cpp`)
   - Handles menus and user flow.
   - Delegates actual operations to the manager/service layer.

2. **Service Layer** (`BookManager`)
   - Encapsulates use-cases (insert, delete, update, search, etc.).
   - Coordinates between input utilities and data-structure APIs.

3. **Domain Layer** (`Book`)
   - Encapsulated entity for library book metadata.
   - Keeps data representation clean and reusable.

4. **Data Structure Layer** (`DoublyLinkedList`)
   - Core linked-list implementation with `prev` and `next` pointers.
   - Owns memory and guarantees list invariants.

5. **Utility Layer** (`InputUtils.h`)
   - Reusable, validated input functions for bounded numeric input and non-empty strings.

### 2.2 Why this Structure?
- **Separation of concerns:** UI logic is isolated from data logic.
- **Maintainability:** each module has a clear responsibility.
- **Testability:** list operations are testable independently.
- **Safety:** memory ownership is centralized in one class (`DoublyLinkedList`).

---

## 3) Detailed Data Structure Implementation

The project uses a **custom Doubly Linked List** (not `std::list`) to demonstrate core pointer-based data-structure skills.

### 3.1 Node Structure
Each node contains:
- `Book data`
- `Node* next` (forward link)
- `Node* prev` (backward link)

### 3.2 Core List State
The list stores:
- `head_`: pointer to first node
- `tail_`: pointer to last node
- `length_`: current number of nodes

### 3.3 Double Pointers (`prev` and `next`)
- `next` enables forward traversal (head -> tail).
- `prev` enables backward traversal (tail -> head).
- Together they make middle-node deletion/insertion efficient because both neighbors are directly reachable.

### 3.4 Traversal
- **Forward traversal**: iterate with `current = current->next`.
- **Backward traversal**: iterate with `current = current->prev`.
- Display functions explicitly support both traversal directions.

### 3.5 Search Implementation
`findByTitle(title)` performs linear search from head to tail and returns:
- pointer to matching `Book` if found,
- `nullptr` otherwise.

### 3.6 Insert Operations
- **Head insert (`insertFront`)**
  - New node becomes `head_`.
  - Previous head (if any) gets `prev = newNode`.
- **Tail insert (`insertBack`)**
  - New node becomes `tail_`.
  - Previous tail (if any) gets `next = newNode`.
- **Middle insert (`insertAt`)**
  - Locate target position node.
  - Relink four pointers safely:
    - `prevNode->next = newNode`
    - `newNode->prev = prevNode`
    - `newNode->next = nextNode`
    - `nextNode->prev = newNode`

### 3.7 Delete Operations
- **Head delete (`removeFront`)**
  - Move `head_` to next node.
  - Update new head `prev = nullptr`.
- **Tail delete (`removeBack`)**
  - Move `tail_` to previous node.
  - Update new tail `next = nullptr`.
- **Position delete (`removeAt`)**
  - Locate node, unlink neighbors, delete node.
- **Delete by title (`removeByTitle`)**
  - Search matching node then delete with proper relinking.

### 3.8 Edge Cases Handled
- Insert/delete on empty list.
- Insert at invalid position.
- Delete at invalid position.
- Duplicate title insertion blocked.
- Deleting the only node updates both `head_` and `tail_`.
- Sorting with size < 2 returns immediately.
- Clear operation resets pointers and length safely.

### 3.9 Complexity Analysis
Let **n** = number of books.

- Search by title: **O(n)** time, **O(1)** extra space.
- Insert head/tail: **O(1)** time, **O(1)** space.
- Insert at position: **O(n)** time (traversal), **O(1)** space.
- Delete head/tail: **O(1)** time, **O(1)** space.
- Delete at position/by title: **O(n)** time worst case, **O(1)** space.
- Sort by title (insertion sort shifting node data): **O(n²)** time, **O(1)** extra space.

---

## 4) Key Features

- Multi-list management (5 independent named lists).
- Strong input validation and normalized yes/no handling.
- Clean class APIs with const-correct methods where applicable.
- Manual pointer handling with deterministic cleanup (`clear`, destructor).
- Unit-style test executable for core linked-list behavior.

---

## 5) Challenges and Solutions

### Challenge 1: Preventing pointer corruption in middle operations
**Solution:** centralized link manipulation with helper methods (`nodeAt`, `unlinkNode`) and explicit head/tail special-case handling.

### Challenge 2: Avoiding memory leaks with raw pointers
**Solution:** single ownership boundary in `DoublyLinkedList`; all allocations happen there and all nodes are destroyed in `clear()` and destructor.

### Challenge 3: Terminal input reliability
**Solution:** reusable input utility functions that validate type/range and always clean the stream buffer.

### Challenge 4: Keeping code readable as features grow
**Solution:** modular architecture and descriptive method names per layer (`insertBookInteractive`, `removeByTitle`, etc.).

---

## 6) Project Structure

```text
.
├── include/
│   ├── book.h
│   ├── DoublyLinked_list.h
│   ├── BooksManage.h
│   └── InputUtils.h
├── src/
│   ├── book.cpp
│   ├── DoublyLinked_list.cpp
│   └── BooksManage.cpp
├── tests/
│   └── test_library.cpp
├── main.cpp
├── CMakeLists.txt
├── CONTRIBUTING.md
├── LICENSE
└── Std_Libraries.h
```

---

## 7) Build and Run

## Requirements
- C++17 compatible compiler (recommended: `g++ 10+` or `clang++ 11+`)
- CMake 3.16+

### Build with g++
```bash
g++ -std=c++17 -Iinclude main.cpp src/BooksManage.cpp src/DoublyLinked_list.cpp src/book.cpp -o library_app
./library_app
```

### Build with CMake
```bash
cmake -S . -B build
cmake --build build
./build/library_app
```

### Run Tests
```bash
ctest --test-dir build --output-on-failure
```

---

## 8) Future Improvements

- Persist lists and books to file (JSON/SQLite).
- Introduce GoogleTest/Catch2 for richer test reports.
- Add CI pipeline (GitHub Actions) for automatic build/test checks.
- Add case-insensitive search and optional fuzzy matching.
- Add command logging and export/import support.
- Improve sorting with merge sort on linked-list nodes to reduce sort complexity.

---

## 9) Portfolio/Evaluation Notes

This repository demonstrates:
- Practical use of doubly linked lists in a full application.
- Safe pointer operations and edge-case handling.
- Layered architecture and clean API design.
- Professional documentation and build/test setup.

