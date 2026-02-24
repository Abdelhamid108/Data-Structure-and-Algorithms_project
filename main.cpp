#include "BooksManage.h"
#include "InputUtils.h"

namespace {

void printMainMenu() {
    std::cout << "\n========== Main Menu ==========\n"
              << "1) Show all lists\n"
              << "2) Create a new list\n"
              << "3) Open an existing list\n"
              << "4) Exit\n";
}

void printListMenu() {
    std::cout << "\n======= Library List Menu =======\n"
              << "1) Insert book\n"
              << "2) Delete book\n"
              << "3) Sort books by title\n"
              << "4) Display books\n"
              << "5) Clear current list\n"
              << "6) Search by title\n"
              << "7) Print number of books\n"
              << "8) Update book\n"
              << "9) Back to main menu\n";
}

}  // namespace

int main() {
    BookManager manager;

    bool running = true;
    while (running) {
        printMainMenu();
        const int choice = io::readBoundedNumber(1, 4, "Select option: ");

        switch (choice) {
            case 1:
                manager.printLists();
                break;
            case 2: {
                const int listIndex = io::readBoundedNumber(1, BookManager::kMaxLists, "List number (1-5): ");
                const std::string listName = io::readNonEmptyLine("List name: ");

                if (manager.createList(listIndex, listName)) {
                    std::cout << "List created successfully.\n";
                } else {
                    std::cout << "Failed to create list. Check index/name.\n";
                }
                break;
            }
            case 3: {
                manager.printLists();
                const int listIndex = io::readBoundedNumber(1, BookManager::kMaxLists, "Open list number (1-5): ");

                if (!manager.openList(listIndex)) {
                    std::cout << "Cannot open this list. Create it first.\n";
                    break;
                }

                bool inListMenu = true;
                while (inListMenu) {
                    printListMenu();
                    const int action = io::readBoundedNumber(1, 9, "Select action: ");

                    switch (action) {
                        case 1: manager.insertBookInteractive(); break;
                        case 2: manager.deleteBookInteractive(); break;
                        case 3: manager.sortBooksInteractive(); break;
                        case 4: manager.displayBooksInteractive(); break;
                        case 5: manager.clearCurrentListInteractive(); break;
                        case 6: manager.searchBookInteractive(); break;
                        case 7: manager.printCurrentListLength(); break;
                        case 8: manager.updateBookInteractive(); break;
                        case 9: inListMenu = false; break;
                    }
                }
                break;
            }
            case 4:
                running = false;
                break;
        }
    }

    std::cout << "\nExiting the program. Goodbye!\n";
    return 0;
}
