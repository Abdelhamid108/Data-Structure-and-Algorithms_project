#pragma once

#include "../Std_Libraries.h"

/**
 * @brief Represents a single book entity in the library.
 *
 * This class is intentionally small and focused on book data only.
 * It exposes a clean API for reading and updating fields while
 * preserving encapsulation.
 */
class Book {
public:
    Book() = default;
    Book(std::string title, std::string author, std::string category, int publishYear);

    [[nodiscard]] const std::string& title() const noexcept;
    [[nodiscard]] const std::string& author() const noexcept;
    [[nodiscard]] const std::string& category() const noexcept;
    [[nodiscard]] int publishYear() const noexcept;

    void setTitle(std::string value);
    void setAuthor(std::string value);
    void setCategory(std::string value);
    void setPublishYear(int value);

    /**
     * @brief Pretty-print all book details.
     */
    void print() const;

private:
    std::string title_;
    std::string author_;
    std::string category_;
    int publishYear_{0};
};
