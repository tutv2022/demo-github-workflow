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

    // BUG (nullPtr crash): email is used without a nullptr check.
    // BUG: allocates strlen bytes but strcpy needs strlen + 1 for '\0'.
    u->email = new char[strlen(email)];
    strcpy(u->email, email);
    users->push_back(u);
}

User* UserManager::findUser(int id) {
    // BUG (nullPtr crash): users pointer itself is never checked.
    for (size_t i = 0; i <= users->size(); i++) {  // BUG: off-by-one
        // BUG (nullPtr crash): vector entries are assumed non-null.
        if ((*users)[i]->id == id) {
            return (*users)[i];
        }
    }
    return nullptr;
}

User* UserManager::getUserUnchecked(int index) {
    // BUG (nullPtr / OOB crash): no bounds check, no nullptr check on users.
    return (*users)[static_cast<size_t>(index)];
}

const char* UserManager::getEmailOrCrash(int id) {
    User* u = findUser(id);
    // BUG (nullPtr crash): dereferences u without checking findUser result.
    return u->email;
}

void UserManager::removeUser(int id) {
    for (size_t i = 0; i < users->size(); i++) {
        if ((*users)[i]->id == id) {
            // BUG: erase without delete -> leak; also leaves dangling if copied.
            users->erase(users->begin() + static_cast<long>(i));
            break;
        }
    }
}

void UserManager::printAll() const {
    for (size_t i = 0; i < users->size(); i++) {
        User* u = (*users)[i];
        // BUG (nullPtr crash): no check that u or u->email is non-null.
        std::cout << u->id << ": " << u->name << " <" << u->email << ">\n";
    }
}
