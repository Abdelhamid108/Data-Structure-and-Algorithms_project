#include "DoublyLinked_list.h"

#include <cassert>

int main() {
    DoublyLinkedList list;

    // Empty-state checks
    assert(list.isEmpty());
    assert(list.size() == 0);
    assert(!list.removeFront());
    assert(!list.removeBack());

    // Insert at head and tail
    assert(list.insertBack(Book{"C", "Author C", "Fiction", 2003}));
    assert(list.insertFront(Book{"A", "Author A", "Fantasy", 2001}));
    assert(list.insertAt(2, Book{"B", "Author B", "Sci-Fi", 2002}));
    assert(list.size() == 3);

    // Duplicate title should be rejected
    assert(!list.insertBack(Book{"B", "Another", "Romance", 2020}));

    // Search
    const Book* found = list.findByTitle("B");
    assert(found != nullptr);
    assert(found->author() == "Author B");

    // Sort
    list.sortByTitle();
    assert(list.findByTitle("A") != nullptr);

    // Delete middle, head, tail
    assert(list.removeAt(2));
    assert(list.size() == 2);
    assert(list.removeByTitle("A"));
    assert(list.removeByTitle("C"));
    assert(list.isEmpty());

    // Clear should keep list valid
    list.clear();
    assert(list.size() == 0);

    return 0;
}
