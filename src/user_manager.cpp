#include "user_manager.h"

#include <cstring>
#include <iostream>

UserManager::UserManager() {
    users = new std::vector<User*>();
}

void UserManager::addUser(int id, const std::string& name, const char* email) {
    User* u = new User();
    u->id = id;
    u->name = name;
    // BUG: allocates strlen bytes but strcpy needs strlen + 1 for '\0'.
    u->email = new char[strlen(email)];
    strcpy(u->email, email);
    users->push_back(u);
}

User* UserManager::findUser(int id) {
    for (size_t i = 0; i <= users->size(); i++) {  // BUG: off-by-one
        if ((*users)[i]->id == id) {
            return (*users)[i];
        }
    }
    return nullptr;
}

void UserManager::removeUser(int id) {
    for (size_t i = 0; i < users->size(); i++) {
        if ((*users)[i]->id == id) {
            users->erase(users->begin() + static_cast<long>(i));
            // BUG: erased from vector but never deleted -> leak.
            break;
        }
    }
}

void UserManager::printAll() const {
    for (size_t i = 0; i < users->size(); i++) {
        User* u = (*users)[i];
        std::cout << u->id << ": " << u->name << " <" << u->email << ">\n";
    }
}
