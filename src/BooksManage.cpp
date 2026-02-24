#include "BooksManage.h"

#include "InputUtils.h"

BookManager::BookManager() = default;

bool BookManager::createList(const int oneBasedIndex, const std::string& listName) {
    if (oneBasedIndex < 1 || oneBasedIndex > kMaxLists || listName.empty()) {
        return false;
    }

    const int index = oneBasedIndex - 1;
    libraries_[index].name = listName;
    libraries_[index].list.clear();
    return true;
}

bool BookManager::openList(const int oneBasedIndex) {
    if (oneBasedIndex < 1 || oneBasedIndex > kMaxLists) {
        return false;
    }

    const int index = oneBasedIndex - 1;
    if (!isListCreated(index)) {
        return false;
    }

    activeListIndex_ = index;
    return true;
}

void BookManager::printLists() const {
    std::cout << "\nAvailable Lists\n";
    std::cout << "---------------\n";
    for (int i = 0; i < kMaxLists; ++i) {
        std::cout << i + 1 << ") " << libraries_[i].name << '\n';
    }
}

void BookManager::insertBookInteractive() {
    std::cout << "\nInsert Options\n"
              << "1) Insert at head\n"
              << "2) Insert at tail\n"
              << "3) Insert at position\n";

    const int choice = io::readBoundedNumber(1, 3, "Choose option: ");
    Book book = buildBookFromInput();

    bool success = false;
    switch (choice) {
        case 1:
            success = activeSlot().list.insertFront(std::move(book));
            break;
        case 2:
            success = activeSlot().list.insertBack(std::move(book));
            break;
        case 3: {
            const int position = io::readBoundedNumber(1, activeSlot().list.size() + 1, "Position (1-based): ");
            success = activeSlot().list.insertAt(position, std::move(book));
            break;
        }
    }

    std::cout << (success ? "Book inserted successfully.\n" : "Insert failed (duplicate title or invalid position).\n");
}

void BookManager::deleteBookInteractive() {
    if (activeSlot().list.isEmpty()) {
        std::cout << "Current list is empty.\n";
        return;
    }

    std::cout << "\nDelete Options\n"
              << "1) Delete head\n"
              << "2) Delete tail\n"
              << "3) Delete by position\n"
              << "4) Delete by title\n";

    const int choice = io::readBoundedNumber(1, 4, "Choose option: ");
    bool success = false;

    switch (choice) {
        case 1:
            success = activeSlot().list.removeFront();
            break;
        case 2:
            success = activeSlot().list.removeBack();
            break;
        case 3: {
            const int position = io::readBoundedNumber(1, activeSlot().list.size(), "Position (1-based): ");
            success = activeSlot().list.removeAt(position);
            break;
        }
        case 4: {
            const std::string title = io::readNonEmptyLine("Book title: ");
            success = activeSlot().list.removeByTitle(title);
            break;
        }
    }

    std::cout << (success ? "Book deleted successfully.\n" : "Delete failed.\n");
}

void BookManager::searchBookInteractive() const {
    if (activeSlot().list.isEmpty()) {
        std::cout << "Current list is empty.\n";
        return;
    }

    const std::string title = io::readNonEmptyLine("Title to search: ");
    const Book* found = activeSlot().list.findByTitle(title);
    if (found == nullptr) {
        std::cout << "Book not found.\n";
        return;
    }

    std::cout << "\nBook Found\n";
    found->print();
}

void BookManager::sortBooksInteractive() {
    if (activeSlot().list.size() < 2) {
        std::cout << "At least two books are required for sorting.\n";
        return;
    }

    if (io::readYesNo("Sort books by title? (y/n): ") == 'y') {
        activeSlot().list.sortByTitle();
        std::cout << "Books sorted by title.\n";
    }
}

void BookManager::displayBooksInteractive() const {
    if (activeSlot().list.isEmpty()) {
        std::cout << "Current list is empty.\n";
        return;
    }

    const int mode = io::readBoundedNumber(1, 2, "Display mode 1) forward 2) backward: ");
    if (mode == 1) {
        activeSlot().list.displayForward();
    } else {
        activeSlot().list.displayBackward();
    }
}

void BookManager::clearCurrentListInteractive() {
    if (activeSlot().list.isEmpty()) {
        std::cout << "Current list is already empty.\n";
        return;
    }

    if (io::readYesNo("Delete all books in current list? (y/n): ") == 'y') {
        activeSlot().list.clear();
        std::cout << "Current list cleared successfully.\n";
    }
}

void BookManager::printCurrentListLength() const {
    std::cout << "Current list contains " << activeSlot().list.size() << " book(s).\n";
}

void BookManager::updateBookInteractive() {
    if (activeSlot().list.isEmpty()) {
        std::cout << "Current list is empty.\n";
        return;
    }

    const std::string existingTitle = io::readNonEmptyLine("Title to update: ");
    Book* target = activeSlot().list.findByTitle(existingTitle);

    if (target == nullptr) {
        std::cout << "Book not found.\n";
        return;
    }

    std::cout << "\nEnter updated data\n";
    const std::string newTitle = io::readNonEmptyLine("New title: ");

    // Prevent creating duplicate titles unless user keeps the same title.
    if (newTitle != existingTitle && activeSlot().list.containsTitle(newTitle)) {
        std::cout << "Update failed: another book already uses this title.\n";
        return;
    }

    target->setTitle(newTitle);
    target->setAuthor(io::readNonEmptyLine("New author: "));

    std::cout << "Category options:\n"
              << "1) Fiction\n2) Mystery / Thriller / Crime\n3) Fantasy\n4) Science Fiction\n5) Romance\n";
    const int categoryChoice = io::readBoundedNumber(1, 5, "Category: ");
    target->setCategory(categoryFromChoice(categoryChoice));

    const int year = io::readBoundedNumber(1000, 2100, "New publish year (1000-2100): ");
    target->setPublishYear(year);

    std::cout << "Book updated successfully.\n";
}

bool BookManager::isListCreated(const int zeroBasedIndex) const {
    return libraries_[zeroBasedIndex].name != "UNSET";
}

BookManager::LibrarySlot& BookManager::activeSlot() {
    return libraries_[activeListIndex_];
}

const BookManager::LibrarySlot& BookManager::activeSlot() const {
    return libraries_[activeListIndex_];
}

Book BookManager::buildBookFromInput() {
    const std::string title = io::readNonEmptyLine("Title: ");
    const std::string author = io::readNonEmptyLine("Author: ");

    std::cout << "Category options:\n"
              << "1) Fiction\n2) Mystery / Thriller / Crime\n3) Fantasy\n4) Science Fiction\n5) Romance\n";
    const int categoryChoice = io::readBoundedNumber(1, 5, "Category: ");
    const int year = io::readBoundedNumber(1000, 2100, "Publish year (1000-2100): ");

    return Book{title, author, categoryFromChoice(categoryChoice), year};
}

std::string BookManager::categoryFromChoice(const int choice) {
    switch (choice) {
        case 1: return "Fiction";
        case 2: return "Mystery / Thriller / Crime";
        case 3: return "Fantasy";
        case 4: return "Science Fiction";
        case 5: return "Romance";
        default: return "Unknown";
    }
}
