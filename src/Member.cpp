#include <iostream>
#include "../include/Member.h"
#include <cmath>

Member::Member(std::string id, std::string name, std::string email) {
    this->memberID = id;
    this->name = name;
    this->email = email;
    this->active = false; // only become active when added to Registry
    borrowed = new LibraryItem*[borrowedCapacity];
    std::cout << "Member " << memberID << " created!" << std::endl;
}

Member::~Member() {
    for (int i=0; i < borrowedCount; i++) {
        borrowed[i] = nullptr;
    }
    delete[] borrowed;
}

bool Member::canBorrow() const {
    return active && borrowedCount <= borrowedCapacity;
}

bool Member::getActive() const {
    return active;
}

void Member::setActive(bool cond) {
    this->active = cond;
}

void Member::addBorrowed(LibraryItem *item) {
    if (item->getType() == "Physical" && item->canBorrow()) {
        PhysicalBook* pb = dynamic_cast<PhysicalBook*>(item);
        pb->checkOut();
        borrowed[borrowedCount++] = pb;
    }
    else if (item->getType() == "EBook") {
        std::cout << "Cannot borrow an EBook!" << std::endl;
    }
}

void Member::removeBorrowed(const std::string &isbn) {
    if (borrowedCount == 0) {
        std::cout << "No borrowed books available" << std::endl;
        return;
    }
    int index;
    for (int i=0; i < borrowedCount; i++) {
        if (borrowed[i]->getISBN() == isbn) {
            index = i;
        }
    }

    borrowed[index] = nullptr;
    if (index != borrowedCount-1) {
        for (int i=index; i < borrowedCount-1; i++) {
            borrowed[i] = borrowed[i+1];
        }
    }

    borrowedCount--;
    borrowed[borrowedCount] = nullptr;
}

void Member::addFee(const double amount, const int daysLate) {
    ;
    for (int i=0; i < borrowedCount; i++) {
        outstandingFees += borrowed[i]->calcLateFee(daysLate);
    }
}

void Member::payFee(double amount) {
    if (amount > outstandingFees) {
        amount = outstandingFees;
    }
    outstandingFees -= amount;
}

void Member::display() const {
    std::cout << "====================================" << std::endl;
    std::cout << "MEMBER PROFILE" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "ID:               " << memberID << std::endl;
    std::cout << "Name:             " << name << std::endl;
    std::cout << "Email:            " << email << std::endl;
    std::cout << "Status:           " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Outstanding Fees: $" << getoutstandingFees() << std::endl;
    std::cout << "Books Borrowed:   " << borrowedCount << " / " << borrowedCapacity << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

int Member::getBorrowedCount() const {
    return borrowedCount;
}

int Member::getBorrowedCapacity() const {
    return borrowedCapacity;
}

double Member::getoutstandingFees() const {
    return round(outstandingFees * 100) / 100;
}

LibraryItem *Member::getBorrowed(std::string isbn) const {
    for (int i=0; i < borrowedCount; i++) {
        if (borrowed[i]->getISBN() == isbn) {
            return borrowed[i];
        }
    }
    return nullptr;
}

std::string Member::getMemberID() const {
    return memberID;
}

LibraryItem *Member::getBorrowedIndex(const int index) const {
    return (index < borrowedCount) ? borrowed[index] : nullptr;
}

int Member::getCatalogueIndex(Catalogue *catalogue, std::string isbn) const {
    return catalogue->getIndex(isbn);
}

void Member::setOutstandingFees(double fees) {
    if (fees < 0)
    {
        this->outstandingFees = 0;
    }
    this->outstandingFees = fees;
}

std::string Member::saveMember(Catalogue *catalogue) const {
    std::string borrowedBooks = "";
    int index;
    if (borrowedCount != 0) {
        for (int i=0; i < borrowedCount; i++) {
            index = getCatalogueIndex(catalogue, this->borrowed[i]->getISBN());
            borrowedBooks += "|" + std::to_string(index);
            if (index == -1) { 
                break;
            }
        }
    }
    int cond = this->getActive();
    return std::format("{}|{}|{}|{}|{}|{}", memberID, name, email, this->getBorrowedCount(), this->getoutstandingFees(), cond) + borrowedBooks;
}

void Member::setBorrowedCount(int count) {
    this->borrowedCount = (count >= 0) ? count: 0;
}