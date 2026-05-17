#include "../include/PhysicalBook.h"
#include <iostream>

PhysicalBook::PhysicalBook(std::string title, std::string author, std::string isbn, int copies) {
    this->title = title;
    this->author= author;
    this->isbn = isbn;
    this->totalCopies = copies;
    this->availableCopies = copies;
}

std::string PhysicalBook::getType() const {
    return "Physical";
}

bool PhysicalBook::canBorrow() const {
    return availableCopies > 0;
}

void PhysicalBook::checkOut() {
    --availableCopies;
}

void PhysicalBook::checkIn() {
    ++availableCopies;\
}

double PhysicalBook::calcLateFee(int daysLate) const {
    return round(daysLate*lateFee * 100) / 100;
}

void PhysicalBook::display() const {
        std::cout << "--- Book Details ---" << std::endl;
        std::cout << "Title:  " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "ISBN:   " << isbn << std::endl;
        std::cout << "Total Copies: " << totalCopies << std::endl;
        std::cout << "Available Copies: " << availableCopies << std::endl;
        std::cout << "--------------------" << std::endl;
}

std::string PhysicalBook::saveBook() const {
    return std::format("P|{}|{}|{}|{}", title, author, isbn, totalCopies);
}