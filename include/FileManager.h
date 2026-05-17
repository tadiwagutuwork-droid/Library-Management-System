#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "Catalogue.h"
#include "MemberRegistry.h"
#include <string>

class FileManager {
private:
    std::string filenameBooks = "../data/books.txt";
    std::string filenameMembers = "../data/members.txt";
    std::string filenameTransactions = "../data/transactions.txt";

public:
    void loadBooks(Catalogue *catalogue) const;
    void saveBooks(Catalogue *catalogue) const;
    void loadRegistry(MemberRegistry *registry) const;
    void saveRegistry(MemberRegistry *registry) const;
};
#endif