#pragma once

#include "book.h"

/**
 * @brief Custom doubly linked list implementation for library books.
 *
 * Design notes:
 * - `head_` points to first node, `tail_` points to last node.
 * - Every node stores two links:
 *   - `next` -> next node toward tail
 *   - `prev` -> previous node toward head
 * - This enables O(1) insertion/deletion at both ends and
 *   bidirectional traversal.
 */
class DoublyLinkedList {
private:
    /**
     * @brief Internal node storing a book and bidirectional pointers.
     */
    struct Node {
        Book data;
        Node* next{nullptr};
        Node* prev{nullptr};

        explicit Node(Book value) : data(std::move(value)) {}
    };

public:
    DoublyLinkedList() = default;
    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    DoublyLinkedList(DoublyLinkedList&& other) noexcept;
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;

    [[nodiscard]] bool isEmpty() const noexcept;
    [[nodiscard]] int size() const noexcept;
    [[nodiscard]] bool containsTitle(const std::string& title) const;

    bool insertFront(Book book);
    bool insertBack(Book book);
    bool insertAt(int oneBasedPosition, Book book);

    bool removeFront();
    bool removeBack();
    bool removeAt(int oneBasedPosition);
    bool removeByTitle(const std::string& title);

    [[nodiscard]] Book* findByTitle(const std::string& title) noexcept;
    [[nodiscard]] const Book* findByTitle(const std::string& title) const noexcept;

    /**
     * @brief Sort nodes in ascending order by title using insertion sort on links.
     */
    void sortByTitle();

    /**
     * @brief Remove all nodes and reset list to empty state.
     */
    void clear();

    /**
     * @brief Display books from head to tail.
     */
    void displayForward() const;

    /**
     * @brief Display books from tail to head.
     */
    void displayBackward() const;

private:
    Node* head_{nullptr};
    Node* tail_{nullptr};
    int length_{0};

    [[nodiscard]] Node* nodeAt(int oneBasedPosition) const;
    void unlinkNode(Node* node);
    static void printTableHeader();
};
