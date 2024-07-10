#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

class Book {
public:
    Book(const std::string& bookID, const std::string& bookName);

    std::string getBookID() const;
    void setBookID(const std::string& bookID);

    std::string getBookName() const;
    void setBookName(const std::string& bookName);

private:
    std::string bookID;
    std::string bookName;
};

#endif // BOOK_HPP