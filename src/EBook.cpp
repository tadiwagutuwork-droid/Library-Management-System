#include "../include/EBook.h"
#include <iostream>

EBook::EBook(std::string title, std::string author, std::string isbn, std::string download_url, double mb) {
    this->title = title;
    this->author= author;
    this->isbn = isbn;
    this->download_url = download_url;
    this->fileSizeMB = mb;
}

std::string EBook::getType() const {
    return "EBook";
}

bool EBook::canBorrow() const {
    return false;
}

double EBook::calcLateFee(int daysLate) const {
    return 0.0;
}

void EBook::display() const {
    std::cout << "========== E-BOOK INFO ==========" << std::endl;
    std::cout << "Title:        " << title << std::endl;
    std::cout << "Author:       " << author << std::endl;
    std::cout << "ISBN:         " << isbn << std::endl;
    std::cout << "Download URL: " << download_url << std::endl;
    std::cout << "File Size:    " << round(fileSizeMB * 100) / 100 << " MB" << std::endl;
    std::cout << "=================================" << std::endl;
}


std::string EBook::getDownloadUrl() const {
    return download_url;
}

double EBook::getFileSizeMB() const {
    return fileSizeMB;
}

std::string EBook::saveBook() const {
    return std::format("E|{}|{}|{}|{}|{}", title, author, isbn, download_url, fileSizeMB);
}