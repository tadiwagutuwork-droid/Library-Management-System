#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <ctime>
#include <cmath>
#include "../include/Member.h"
#include "../include/MemberRegistry.h"
#include "../include/Catalogue.h"
#include "../include/PhysicalBook.h"
#include "../include/LibraryItem.h"

class Transaction {
private:
    std::string transactionID, memberID, isbn;
    std::time_t borrowDate, returnDate;
    bool returned;
    const long double borrowedTime = round(7*24*60*60 * 100) / 100;
    double feePaid;

public:
    Transaction(std::string tId, std::string mId, std::string isbn);
    void complete(std::time_t returnDate, double fee, MemberRegistry *registry, Catalogue *catalogue);
    bool isOverdue() const;
    void display() const;
};
#endif