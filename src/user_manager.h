#pragma once

#include <string>
#include <vector>

struct User {
    int id;
    std::string name;
    char* email;
};

class UserManager {
public:
    UserManager();
    // BUG: no destructor -> the vector and every User* leak.

    void addUser(int id, const std::string& name, const char* email);
    User* findUser(int id);
    void removeUser(int id);
    void printAll() const;

    std::vector<User*>* users;  // Public mutable pointer, no encapsulation.
};
