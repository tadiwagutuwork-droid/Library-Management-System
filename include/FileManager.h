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

public:
    void loadBooks(Catalogue *catalogue) const;
    void saveBooks(Catalogue *catalogue) const;
    void loadRegistry(MemberRegistry *registry, Catalogue *catalogue) const;
    void saveRegistry(MemberRegistry *registry, Catalogue *catalogue) const;
};
#endif