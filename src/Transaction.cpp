#include "../include/Transaction.h"
#include <iostream>
#include <ctime>

Transaction::Transaction(std::string tId, std::string mId, std::string isbn) {
    this->transactionID = tId;
    this->memberID = mId;
    this->isbn = isbn;
    this->returned = false;
    this->returnDate = 0;
    this->borrowDate = std::time(nullptr);
}

bool Transaction::isOverdue() const {
    return std::difftime(returnDate, borrowDate) > borrowedTime;
}

void Transaction::complete(std::time_t returnDate, double fee, MemberRegistry *registry, Catalogue *catalogue){
    Member *member = registry->getMember(memberID);
    LibraryItem *book = catalogue->findByISBN(isbn);
    if (book->getType() == "EBook"){
        std::cout << "Cannot return an EBook!" << std::endl;
        return;
    }
    if (!member) {
        std::cerr << "No member found or not active!" << std::endl;
        return;
    }
    this->feePaid = fee;
    PhysicalBook *pb = dynamic_cast<PhysicalBook *>(book);
    if (isOverdue()) {
        int overDueDays = round((std::difftime(returnDate, borrowDate) - borrowedTime) / borrowedTime);
        double charge = pb->calcLateFee(overDueDays);
        member->addFee(charge, overDueDays);
        member->payFee(fee);
    }
    member->removeBorrowed(isbn);
    this->returnDate = returnDate;
    this->returned = true;
    pb->checkIn();
}

std::string formatTime(std::time_t rawTime)
{
    if (rawTime == 0)
        return "N/A"; 

    std::tm *timeInfo = std::localtime(&rawTime);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return std::string(buffer);
}

void Transaction::display() const {
    std::cout << "========================================\n";
    std::cout << "           TRANSACTION DETAILS          \n";
    std::cout << "========================================\n";
    std::cout << "Transaction ID : " << transactionID << "\n";
    std::cout << "Member ID      : " << memberID << "\n";
    std::cout << "Book ISBN      : " << isbn << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Borrow Date    : " << formatTime(borrowDate) << "\n";

    if (returned) {
        std::cout << "Status         : Returned\n";
        std::cout << "Return Date    : " << formatTime(returnDate) << "\n";
        std::cout << "Fee Paid       : $" << std::fixed << std::setprecision(2) << feePaid << "\n";
    }
    else {
        std::cout << "Status         : OUTSTANDING\n";
        std::cout << "Overdue        : " << (isOverdue() ? "YES" : "No") << "\n";
    }
    std::cout << "========================================\n\n";
}

