#ifndef MEMBER_H
#define MEMBER_H
#include "LibraryItem.h"
#include <string>

class Member {
private:
    std::string memberID, name, email;
    bool active;
    int borrowedCount = 0;
    const int borrowedCapacity = 2;
    double outstandingFees = 0;
    LibraryItem **borrowed; // array of pointers to dynamic LibraryItems

public:
    Member(std::string id, std::string name, std::string email);
    ~Member();

    bool canBorrow() const;
    void addBorrowed(LibraryItem *item);
    void removeBorrowed(const std::string &isbn);
    void addFee(const double amount, const int daysLate);
    void payFee(double amount);
    void display() const;
    bool getActive() const;
    int getBorrowedCount() const;
    int getBorrowedCapacity() const;
    double getoutstandingFees() const;
    LibraryItem *getBorrowed(std::string isbn) const;
    LibraryItem *getBorrowedIndex(const int index) const;
    void setActive(bool cond);
    std::string getMemberID() const;
    std::string saveMember() const;
};
#endif