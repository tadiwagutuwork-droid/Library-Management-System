#include "../include/Catalogue.h"
#include "../include/PhysicalBook.h"
#include "../include/EBook.h"
#include "../include/Member.h"
#include "../include/MemberRegistry.h"
#include <iostream>

int main() {
    std::cout << "== Library System — Automated Test Main ==\n";

    Catalogue catalogue;
    MemberRegistry registry;

    // Create and add books
    PhysicalBook *p1 = new PhysicalBook("The C++ Way", "Bjarne", "ISBN-001", 2);
    EBook *e1 = new EBook("Effective Modern C++", "Scott", "ISBN-002", "http://example.com/effective", 3.4);

    catalogue.add(p1);
    catalogue.add(e1);

    std::cout << "Added books -> count: " << catalogue.getCount() << "\n";

    // Create and register a member
    Member *m1 = new Member("M001", "Alice", "alice@example.com");
    registry.addToRegistry(m1);
    m1->setActive(true);

    std::cout << "Registered members -> count: " << registry.getMemberCount() << "\n";

    // Borrow a physical book
    LibraryItem *phys = catalogue.findByISBN("ISBN-001");
    if (phys && phys->canBorrow()) {
        m1->addBorrowed(phys);
        std::cout << "Member borrowed physical book (ISBN-001).\n";
    } else {
        std::cout << "Physical book not available for borrow.\n";
    }

    // Attempt to borrow an EBook (should be rejected)
    LibraryItem *ebook = catalogue.findByISBN("ISBN-002");
    m1->addBorrowed(ebook);

    // Display member profile
    m1->display();

    // Return the physical book
    m1->removeBorrowed("ISBN-001");
    std::cout << "After returning, borrowed count: " << m1->getBorrowedCount() << "\n";

    // Simulate late fee calculation
    m1->setBorrowedCount(1); // pretend 1 book borrowed
    m1->addFee(0.0, 5); // 5 days late
    std::cout << "Outstanding fees (after 5 days late): $" << m1->getoutstandingFees() << "\n";

    std::cout << "== Test finished ==\n";

    // Note: Catalogue destructor will delete contained books; registry destructor will manage members.
    return 0;
}
