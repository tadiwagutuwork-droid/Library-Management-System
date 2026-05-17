#include "../include/FileManager.h"
#include <sstream>
#include <fstream>
#include <iostream>

void FileManager::loadBooks(Catalogue *catalogue) const {
    std::ifstream inFile(filenameBooks);
    std::string file;

    if (!inFile)
    {
        return;
    }

    while (getline(inFile, file))
    {
        std::istringstream ss(file);
        std::string temp;
        char bookType;
        std::string title, author, isbn;
        PhysicalBook *pbook;
        EBook *ebook;

        // 1. Get ID
        if (std::getline(ss, temp, '|'))
        {
            char bookType = temp[0];
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
        outFile << catalogue[i].getAt(i)->saveBook() << std::endl;
    }
}

void FileManager::loadRegistry(MemberRegistry *registry) const {
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
        member = nullptr;
    }
    inFile.close();
}

void FileManager::saveRegistry(MemberRegistry *registry) const {
    std::ofstream outFile(filenameBooks);
    if (!outFile) {
        std::cerr << "Unable to open file for writing!" << std::endl;
        return;
    }
    for (int i = 0; i < registry->getMemberCount(); i++) {
        outFile << registry->getMemberIndex(i) << std::endl;
    }
}