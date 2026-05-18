#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "Catalogue.h"
#include "MemberRegistry.h"
#include "Transaction.h"
#include <string>
#include <sstream>
#include <ctime>

class FileManager {
private:
    std::string filenameBooks = "../data/books.txt";
    std::string filenameMembers = "../data/members.txt";
    std::string filenameTransactions = "../data/transactions.txt";

public:
    void loadBooks(Catalogue *catalogue) const;
    void saveBooks(Catalogue *catalogue) const;
    void loadRegistry(MemberRegistry *registry, Catalogue *catalogue) const;
    void saveRegistry(MemberRegistry *registry, Catalogue *catalogue) const;
    void loadTransactions(Transaction *transaction) const;
    void saveTransactions(Transaction *transaction) const;
};
#endif