#ifndef EBOOK_H
#define EBOOK_H
#include "LibraryItem.h"
#include <string>
#include <cmath>

class EBook: public LibraryItem {
private:
    std::string download_url;
    double fileSizeMB;

public:
    EBook(std::string title, std::string author, std::string isbn, std::string download_url, double mb);

    std::string getType() const override;
    bool canBorrow() const override;
    double calcLateFee(int daysLate) const override;
    void display() const override;
    std::string getDownloadUrl() const; //getter
    double getFileSizeMB() const; //getter
    std::string saveBook() const override;
};

#endif