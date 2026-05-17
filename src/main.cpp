#include <iostream>
#include <ctime>

#include "../include/PhysicalBook.h"
#include "../include/EBook.h"
#include "../include/Member.h"
#include "../include/MemberRegistry.h"
#include "../include/Catalogue.h"
#include "../include/Transaction.h"

using namespace std;

int main()
{

    // =========================================
    // CREATE CATALOGUE
    // =========================================

    Catalogue catalogue;

    // =========================================
    // CREATE BOOKS
    // =========================================

    PhysicalBook *book1 = new PhysicalBook(
        "The Hobbit",
        "J.R.R Tolkien",
        "1111",
        5);

    PhysicalBook *book2 = new PhysicalBook(
        "Clean Code",
        "Robert Martin",
        "2222",
        3);

    EBook *ebook1 = new EBook(
        "C++ Primer",
        "Lippman",
        "3333",
        "https://ebooks.com/cppprimer",
        15.5);

    // =========================================
    // ADD BOOKS TO CATALOGUE
    // =========================================

    catalogue.add(book1);
    catalogue.add(book2);
    catalogue.add(ebook1);

    // =========================================
    // CREATE MEMBERS
    // =========================================

    Member *m1 = new Member(
        "M001",
        "Tadiwa",
        "tadiwa@gmail.com");

    Member *m2 = new Member(
        "M002",
        "John",
        "john@gmail.com");

    // =========================================
    // CREATE REGISTRY
    // =========================================

    MemberRegistry registry;

    registry.addToRegistry(m1);
    registry.addToRegistry(m2);

    // =========================================
    // DISPLAY REGISTRY
    // =========================================

    cout << "\n========== MEMBERS ==========\n"
         << endl;

    registry.displayRegistry();

    // =========================================
    // BORROW BOOKS
    // =========================================

    cout << "\n========== BORROWING ==========\n"
         << endl;

    m1->addBorrowed(book1);
    m1->addBorrowed(book2);

    // should fail
    m1->addBorrowed(ebook1);

    // =========================================
    // DISPLAY BORROWED BOOKS
    // =========================================

    cout << "\n========== BORROWED BOOKS ==========\n"
         << endl;

    for (int i = 0; i < m1->getBorrowedCount(); i++)
    {

        LibraryItem *item = m1->getBorrowedIndex(i);

        if (item != nullptr)
        {
            item->display();
            cout << endl;
        }
    }

    // =========================================
    // CREATE TRANSACTION
    // =========================================

    cout << "\n========== TRANSACTION ==========\n"
         << endl;

    Transaction t1(
        "T001",
        "M001",
        "1111");

    t1.display();

    // =========================================
    // SIMULATE RETURN
    // =========================================

    cout << "\n========== RETURNING BOOK ==========\n"
         << endl;

    time_t returnTime = std::time(nullptr);

    t1.complete(
        returnTime,
        20.0,
        &registry,
        &catalogue);

    t1.display();

    // =========================================
    // DISPLAY MEMBER AFTER RETURN
    // =========================================

    cout << "\n========== MEMBER AFTER RETURN ==========\n"
         << endl;

    m1->display();

    // =========================================
    // DISPLAY CATALOGUE BOOK
    // =========================================

    cout << "\n========== BOOK STATUS ==========\n"
         << endl;

    book1->display();

    return 0;
}