#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H
#include <string>
#include <format>

class LibraryItem {
protected:
    std::string title, author, isbn;
    int borrowCount;

public:
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    int getBorrowCount() const;
    void incrementBorrowCount();
    std::string getFileName() const;

    // Abstract Methods
    virtual std::string getType() const = 0; // wont modify anything
    virtual void display() const = 0;
    virtual bool canBorrow() const = 0;
    virtual double calcLateFee(int daysLate) const = 0;
    virtual std::string saveBook() const = 0;
};

#endif