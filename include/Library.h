#ifndef LIBRARY_H
#define LIBRARY_H
#include "Catalogue.h"
#include "MemberRegistry.h"
#include <string>

class Library {
private:
    Catalogue catalogue;
    MemberRegistry registry;

public:
    void borrowBook(std::string memberID, std::string isbn);
    void returnBook(std::string memberID, std::string isbn);
    void showOverdueReport() const;
    void showTopBorrowed() const;
    void showFeesReport() const;
};

#endif