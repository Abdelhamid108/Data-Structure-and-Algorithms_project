#pragma once

#include "DoublyLinked_list.h"

/**
 * @brief Application service coordinating user actions across multiple lists.
 */
class BookManager {
public:
    static constexpr int kMaxLists = 5;

    BookManager();

    bool createList(int oneBasedIndex, const std::string& listName);
    bool openList(int oneBasedIndex);
    void printLists() const;

    void insertBookInteractive();
    void deleteBookInteractive();
    void searchBookInteractive() const;
    void sortBooksInteractive();
    void displayBooksInteractive() const;
    void clearCurrentListInteractive();
    void printCurrentListLength() const;
    void updateBookInteractive();

private:
    struct LibrarySlot {
        std::string name{"UNSET"};
        DoublyLinkedList list;
    };

    std::array<LibrarySlot, kMaxLists> libraries_{};
    int activeListIndex_{0};

    [[nodiscard]] bool isListCreated(int zeroBasedIndex) const;
    [[nodiscard]] LibrarySlot& activeSlot();
    [[nodiscard]] const LibrarySlot& activeSlot() const;
    static Book buildBookFromInput();
    static std::string categoryFromChoice(int choice);
};
