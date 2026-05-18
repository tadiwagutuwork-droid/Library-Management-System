#ifndef CATALOGUE_H
#define CATALOGUE_H
#include "LibraryItem.h"
#include "PhysicalBook.h"
#include "EBook.h"

class Catalogue {
private:
    LibraryItem **items;
    int count, capacity;

public:
    Catalogue();
    ~Catalogue();

    void add(LibraryItem *item); // single item of Library
    void remove(const std::string &isbn);
    LibraryItem *findByISBN(const std::string &isbn);
    LibraryItem *search(const std::string &query, int &resultCount); // returns heap array
    void display() const;
    int getCount() const;
    int getCapacity() const;
    LibraryItem *getAt(int index) const;
    int getIndex(const std::string &isbn) const;
};
#endif