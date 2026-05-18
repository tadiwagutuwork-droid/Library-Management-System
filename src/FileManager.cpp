#include "../include/FileManager.h"
#include <iostream>
#include <fstream>

void FileManager::loadBooks(Catalogue *catalogue) const {
    std::ifstream inFile(filenameBooks);
    std::string file;

    if (!inFile) {
        return;
    }

    while (getline(inFile, file)) {
        std::istringstream ss(file);
        std::string temp;
        char bookType;
        std::string title, author, isbn;
        PhysicalBook *pbook;
        EBook *ebook;

        if (std::getline(ss, temp, '|'))
        {
            bookType = temp[0];
        }

        std::getline(ss, title, '|');
        std::getline(ss, author, '|');
        std::getline(ss, isbn, '|');

        if (bookType == 'P') {
            int copies;
            if (std::getline(ss, temp, '|')) {
               copies = std::stoi(temp);
            }

            PhysicalBook *pbook = new PhysicalBook(title, author, isbn, copies);
            catalogue->add(pbook);
            pbook = nullptr;
        }
        else {
            std::string download_url;
            double fileSizeMB;
            std::getline(ss, download_url, '|');

            if (std::getline(ss, temp, '|')) {
                fileSizeMB = std::stod(temp);
            }
            EBook *ebook = new EBook(title, author, isbn, download_url, fileSizeMB);
            catalogue->add(ebook);
            ebook = nullptr;
        }
        
    }
    inFile.close();
}

void FileManager::saveBooks(Catalogue *catalogue) const{
    std::ofstream outFile(filenameBooks);
    if (!outFile) {
        std::cerr << "Unable to open file for writing!" << std::endl;
        return;
    }
    for (int i = 0; i < catalogue->getCount(); i++) {
        outFile << catalogue->getAt(i)->saveBook() << std::endl;
    }
}

void FileManager::loadRegistry(MemberRegistry *registry, Catalogue *catalogue) const {
    std::ifstream inFile(filenameMembers);
    std::string file;

    if (!inFile)
    {
        return;
    }

    while (getline(inFile, file))
    {
        std::istringstream ss(file);
        std::string temp;
        std::string mID, name, email;

        std::getline(ss, mID, '|');
        std::getline(ss, name, '|');
        std::getline(ss, email, '|');

        Member *member = new Member(mID, name, email);
        registry->addToRegistry(member);
        int borrowed = 0, x;

        if (std::getline(ss, temp, '|')) {
            borrowed = std::stoi(temp);
        }

        if (std::getline(ss, temp, '|')) {
            member->setOutstandingFees(std::stod(temp));
        }

        if (std::getline(ss, temp, '|')) {
            member->setActive(std::stoi(temp));
        }

        while (borrowed > 0) {
            x = -1;
            if (std::getline(ss, temp, '|')) {
                x = std::stoi(temp);
            }
            if (x == -1) {
                break;
            }
            LibraryItem *item = catalogue->getAt(x);
            if (item != nullptr) {
                member->addBorrowed(item);
            }
        }
        member = nullptr;
    }
    inFile.close();
}

void FileManager::saveRegistry(MemberRegistry *registry, Catalogue *catalogue) const {
    std::ofstream outFile(filenameMembers);
    if (!outFile) {
        std::cerr << "Unable to open file for writing!" << std::endl;
        return;
    }
    for (int i = 0; i < registry->getMemberCount(); i++) {
        outFile << registry->getMemberIndex(i)->saveMember(catalogue) << std::endl;
    }
}

void FileManager::saveTransactions(Transaction *transaction) const{
    std::ofstream outFile(filenameTransactions);
    if (!outFile)
    {
        std::cerr << "Unable to open file for writing!" << std::endl;
        return;
    }
    outFile << transaction->saveData() << std::endl;
}

void FileManager::loadTransactions(Transaction *transaction) const{
    
}

std::time_t stringToTime(const std::string &time_str)
    {
        std::tm t = {};
        std::istringstream ss(time_str);
        ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");

        if (ss.fail())
        {
            std::cerr << "Error: Failed to parse time string.\n";
            return -1;
        }

        // Let the system handle Daylight Saving Time evaluation
        t.tm_isdst = -1;

        return std::mktime(&t);
    }