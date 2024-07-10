#include "Book.hpp"

Book::Book(const std::string& bookID, const std::string& bookName)
    : bookID(bookID), bookName(bookName) {}

std::string Book::getBookID() const {
    return bookID;
}

void Book::setBookID(const std::string& bookID) {
    this->bookID = bookID;
}

std::string Book::getBookName() const {
    return bookName;
}

void Book::setBookName(const std::string& bookName) {
    this->bookName = bookName;
}