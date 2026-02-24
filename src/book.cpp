#include "book.h"

Book::Book(std::string title, std::string author, std::string category, int publishYear)
    : title_(std::move(title)),
      author_(std::move(author)),
      category_(std::move(category)),
      publishYear_(publishYear) {}

const std::string& Book::title() const noexcept { return title_; }
const std::string& Book::author() const noexcept { return author_; }
const std::string& Book::category() const noexcept { return category_; }
int Book::publishYear() const noexcept { return publishYear_; }

void Book::setTitle(std::string value) { title_ = std::move(value); }
void Book::setAuthor(std::string value) { author_ = std::move(value); }
void Book::setCategory(std::string value) { category_ = std::move(value); }
void Book::setPublishYear(const int value) { publishYear_ = value; }

void Book::print() const {
    std::cout << "Title        : " << title_ << '\n'
              << "Author       : " << author_ << '\n'
              << "Category     : " << category_ << '\n'
              << "Publish Year : " << publishYear_ << '\n';
}
