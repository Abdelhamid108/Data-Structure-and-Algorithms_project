#include "DoublyLinked_list.h"

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& other) noexcept
    : head_(other.head_), tail_(other.tail_), length_(other.length_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.length_ = 0;
}

DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    length_ = other.length_;

    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.length_ = 0;
    return *this;
}

bool DoublyLinkedList::isEmpty() const noexcept {
    return head_ == nullptr;
}

int DoublyLinkedList::size() const noexcept {
    return length_;
}

bool DoublyLinkedList::containsTitle(const std::string& title) const {
    return findByTitle(title) != nullptr;
}

bool DoublyLinkedList::insertFront(Book book) {
    if (containsTitle(book.title())) {
        return false;
    }

    Node* newNode = new Node(std::move(book));
    newNode->next = head_;

    if (head_ != nullptr) {
        head_->prev = newNode;
    } else {
        tail_ = newNode;
    }

    head_ = newNode;
    ++length_;
    return true;
}

bool DoublyLinkedList::insertBack(Book book) {
    if (containsTitle(book.title())) {
        return false;
    }

    Node* newNode = new Node(std::move(book));
    newNode->prev = tail_;

    if (tail_ != nullptr) {
        tail_->next = newNode;
    } else {
        head_ = newNode;
    }

    tail_ = newNode;
    ++length_;
    return true;
}

bool DoublyLinkedList::insertAt(const int oneBasedPosition, Book book) {
    if (oneBasedPosition < 1 || oneBasedPosition > length_ + 1 || containsTitle(book.title())) {
        return false;
    }

    if (oneBasedPosition == 1) {
        return insertFront(std::move(book));
    }

    if (oneBasedPosition == length_ + 1) {
        return insertBack(std::move(book));
    }

    Node* nextNode = nodeAt(oneBasedPosition);
    Node* prevNode = nextNode->prev;
    Node* newNode = new Node(std::move(book));

    newNode->next = nextNode;
    newNode->prev = prevNode;
    prevNode->next = newNode;
    nextNode->prev = newNode;

    ++length_;
    return true;
}

bool DoublyLinkedList::removeFront() {
    if (isEmpty()) {
        return false;
    }

    Node* oldHead = head_;
    head_ = head_->next;

    if (head_ != nullptr) {
        head_->prev = nullptr;
    } else {
        tail_ = nullptr;
    }

    delete oldHead;
    --length_;
    return true;
}

bool DoublyLinkedList::removeBack() {
    if (isEmpty()) {
        return false;
    }

    Node* oldTail = tail_;
    tail_ = tail_->prev;

    if (tail_ != nullptr) {
        tail_->next = nullptr;
    } else {
        head_ = nullptr;
    }

    delete oldTail;
    --length_;
    return true;
}

bool DoublyLinkedList::removeAt(const int oneBasedPosition) {
    if (oneBasedPosition < 1 || oneBasedPosition > length_) {
        return false;
    }

    if (oneBasedPosition == 1) {
        return removeFront();
    }

    if (oneBasedPosition == length_) {
        return removeBack();
    }

    Node* target = nodeAt(oneBasedPosition);
    unlinkNode(target);
    delete target;
    --length_;
    return true;
}

bool DoublyLinkedList::removeByTitle(const std::string& title) {
    Node* target = head_;
    while (target != nullptr) {
        if (target->data.title() == title) {
            break;
        }
        target = target->next;
    }

    if (target == nullptr) {
        return false;
    }

    if (target == head_) {
        return removeFront();
    }

    if (target == tail_) {
        return removeBack();
    }

    unlinkNode(target);
    delete target;
    --length_;
    return true;
}

Book* DoublyLinkedList::findByTitle(const std::string& title) noexcept {
    Node* current = head_;
    while (current != nullptr) {
        if (current->data.title() == title) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

const Book* DoublyLinkedList::findByTitle(const std::string& title) const noexcept {
    const Node* current = head_;
    while (current != nullptr) {
        if (current->data.title() == title) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void DoublyLinkedList::sortByTitle() {
    if (length_ < 2) {
        return;
    }

    for (Node* i = head_->next; i != nullptr; i = i->next) {
        Book key = i->data;
        Node* j = i->prev;

        while (j != nullptr && j->data.title() > key.title()) {
            j->next->data = j->data;
            j = j->prev;
        }

        if (j == nullptr) {
            head_->data = std::move(key);
        } else {
            j->next->data = std::move(key);
        }
    }
}

void DoublyLinkedList::clear() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
}

void DoublyLinkedList::displayForward() const {
    printTableHeader();
    int index = 1;
    for (Node* current = head_; current != nullptr; current = current->next) {
        std::cout << std::left << std::setw(6) << index++
                  << std::setw(28) << current->data.title()
                  << std::setw(24) << current->data.author()
                  << std::setw(8) << current->data.publishYear()
                  << current->data.category() << '\n';
    }
}

void DoublyLinkedList::displayBackward() const {
    printTableHeader();
    int index = 1;
    for (Node* current = tail_; current != nullptr; current = current->prev) {
        std::cout << std::left << std::setw(6) << index++
                  << std::setw(28) << current->data.title()
                  << std::setw(24) << current->data.author()
                  << std::setw(8) << current->data.publishYear()
                  << current->data.category() << '\n';
    }
}

DoublyLinkedList::Node* DoublyLinkedList::nodeAt(const int oneBasedPosition) const {
    if (oneBasedPosition < 1 || oneBasedPosition > length_) {
        return nullptr;
    }

    if (oneBasedPosition <= length_ / 2) {
        Node* current = head_;
        for (int i = 1; i < oneBasedPosition; ++i) {
            current = current->next;
        }
        return current;
    }

    Node* current = tail_;
    for (int i = length_; i > oneBasedPosition; --i) {
        current = current->prev;
    }
    return current;
}

void DoublyLinkedList::unlinkNode(Node* node) {
    Node* previous = node->prev;
    Node* next = node->next;

    if (previous != nullptr) {
        previous->next = next;
    }

    if (next != nullptr) {
        next->prev = previous;
    }
}

void DoublyLinkedList::printTableHeader() {
    std::cout << std::left << std::setw(6) << "No."
              << std::setw(28) << "Title"
              << std::setw(24) << "Author"
              << std::setw(8) << "Year"
              << "Category\n"
              << std::string(88, '-') << '\n';
}
