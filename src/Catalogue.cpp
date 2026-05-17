#include "../include/Catalogue.h"
#include <iostream>

Catalogue::Catalogue() {
    capacity = 10;
    count = 0;
    items = new LibraryItem*[capacity];
}

Catalogue::~Catalogue() {
    for (int i=0; i < count; i++) {
        delete items[i];
        items[i] = nullptr;
    }
    delete[] items;
}

void Catalogue::add(LibraryItem *item) {
    items[count++] = item;

    if (count == Catalogue::getCapacity()) {
        this->capacity *= 2;
        LibraryItem **temp = new LibraryItem*[capacity];

        for (int i=0; i < count; i++) {
            temp[i] = items[i];
        }
        delete[] items;
        items = nullptr;

        this->items = temp;
        temp = nullptr; // don't delete, to stop items from being a dangling pointer
    }
}

void Catalogue::remove(const std::string &isbn) {
    bool found = false;
    int index;
    for (int i=0; i < count; i++) {
        if (items[i]->getISBN() != isbn && !found) {
            if (i == count) {
                std::cerr << "ISBN Not Found" << std::endl;
                return;
            }
            continue;
        }
        index = i;
        break;
    }

    std::string message = items[index]->getTitle() + " Book successfully removed";
    items[index] = nullptr;
    if (index != count-1) {
        while (index < count-1) {
            items[index] = items[index + 1];
            ++index;
        }
    }
    count--;
    items[count] = nullptr;
    std::cout << message << std::endl;
}

LibraryItem *Catalogue::findByISBN(const std::string &isbn) {
    for (int i=0; i < count; i++) {
        if (items[i]->getISBN() == isbn) {
            return items[i];
        }
    }
    return nullptr;
}

LibraryItem *Catalogue::search(const std::string &query, int &resultCount) {
    int size = 0;
    for (int i=0; i < count; i++) {
        if (items[i]->getTitle() == query || items[i]->getAuthor() == query) {
            ++size;
        }
    }
    if (size == 0) {
        return nullptr;
    }

    LibraryItem **results = new LibraryItem*[size];
    int index = 0;
    for (int i=0; i < count; i++) {
        if (items[i]->getTitle() == query || items[i]->getAuthor() == query) {
            results[index++] = items[i];
        }
    }

    return *results;
}

void Catalogue::display() const {
    for (int i=0; i < count; i++) {
        items[i]->display();
        std::cout << "\n";
    }
}

int Catalogue::getCount() const {
    return count;
}

int Catalogue::getCapacity() const {
    return capacity;
}

LibraryItem *Catalogue::getAt(int index) const {
    return (index < count) ? items[index] : nullptr;
}