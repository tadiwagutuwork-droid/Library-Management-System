#ifndef MEMBERREGISTRY_H
#define MEMBERREGISTRY_H
#include "Member.h"
#include <string>

class MemberRegistry {
private:
    int memberCount = 0;
    int memberCapacity = 10;
    Member **registry; // dynamic array of Members
    
public:
    MemberRegistry();
    ~MemberRegistry();
    void addToRegistry(Member *member);
    void removeFromRegistry(Member *member);
    void displayRegistry();
    Member *getMember(std::string memberID) const;
    Member *getMemberIndex(int index) const;
    int getMemberCount() const;
};

#endif