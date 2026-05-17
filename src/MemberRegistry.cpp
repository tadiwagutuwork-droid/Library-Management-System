#include "../include/MemberRegistry.h"
#include <iostream>

MemberRegistry::MemberRegistry() {
    registry = new Member*[memberCapacity];
}

MemberRegistry::~MemberRegistry() {
    for (int i=0; i < memberCount; i++) {
        delete registry[i];
        registry[i] = nullptr;
    }
    delete[] registry;
}

void MemberRegistry::addToRegistry(Member *member) {
    member->setActive(true);
    registry[memberCount] = member;
    memberCount++;
    if (memberCount == memberCapacity) {
        memberCapacity *= 2;
        Member **temp = new Member*[memberCapacity];

        for (int i=0; i < memberCount; i++) {
            temp[i] = registry[i];
        }
        delete[] registry;
        registry = nullptr;

        this->registry = temp;
        temp = nullptr;
    }
}

void MemberRegistry::removeFromRegistry(Member *member) {
    member->setActive(false);
    int index;
    for (int i = 0; i < memberCount; i++) {
        if (registry[i] == member) {
            index = i;
            break;
        }
    }

    std::string message = "Member successfully removed";
    registry[index] = nullptr;
    if (index != memberCount - 1) {
        while (index < memberCount - 1) {
            registry[index] = registry[index + 1];
            ++index;
        }
    }
    memberCount--;
    registry[memberCount] = nullptr;
    std::cout << message << std::endl;
}

void MemberRegistry::displayRegistry() {
    for (int i=0; i < memberCount; i++) {
        registry[i]->display();
        std::cout << std::endl;
    }
}

Member *MemberRegistry::getMember(std::string memberID) const {
    for (int i = 0; i < memberCount; i++) {
        if (registry[i]->getMemberID() == memberID && registry[i]->getActive()) {
            return registry[i];
        }
    }
    return nullptr;
}

Member *MemberRegistry::getMemberIndex(int index) const
{
    return (index < memberCount && index >= 0) ? registry[index] : nullptr;
}

int MemberRegistry::getMemberCount() const {
    return memberCount;
}