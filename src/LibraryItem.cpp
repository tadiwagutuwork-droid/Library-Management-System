#include "../include/LibraryItem.h"

std::string LibraryItem::getTitle() const {
    return this->title;
}

std::string LibraryItem::getAuthor() const {
    return author;
}

std::string LibraryItem::getISBN() const {
    return isbn;
}

int LibraryItem::getBorrowCount() const {
    return borrowCount;
}

void LibraryItem::incrementBorrowCount() {
    ++borrowCount;
}
