#include "../include/Catalogue.h"
#include "../include/MemberRegistry.h"
#include "../include/FileManager.h"

#include <iostream>

int main()
{

    Catalogue catalogue;
    MemberRegistry registry;
    FileManager fileManager;

    // Load books FIRST
    fileManager.loadBooks(&catalogue);

    // THEN load members
    fileManager.loadRegistry(&registry, &catalogue);

    std::cout << "\nMembers Loaded Successfully\n";

    catalogue.display();
    registry.displayRegistry();

    return 0;
}