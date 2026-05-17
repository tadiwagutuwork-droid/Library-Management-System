#ifndef PHYSICALBOOK_H
#define PHYSICALBOOK_H
#include "LibraryItem.h"
#include <string>
#include <cmath>

class PhysicalBook: public LibraryItem {
private:
    int totalCopies, availableCopies;
    const double lateFee = 2.50;

public:
    PhysicalBook(std::string title, std::string author, std::string isbn, int copies);
    
    std::string getType() const override;
    bool canBorrow() const override;
    double calcLateFee(int daysLate) const override;
    void display() const override;
    std::string saveBook() const override;
    void checkOut();
    void checkIn();
};
#endif 
