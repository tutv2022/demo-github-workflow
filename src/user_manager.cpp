#include <iostream>
#include <string>
#include <vector>
#include <cstring>

// Simple user management module used to exercise the AI reviewer.
// It intentionally contains bugs, leaks, and questionable design choices.

struct User {
    int id;
    std::string name;
    char* email;
};

class UserManager {
public:
    UserManager() {
        users = new std::vector<User*>();
    }

    // BUG: no destructor -> the vector and every User* leak.

    void addUser(int id, const std::string& name, const char* email) {
        User* u = new User();
        u->id = id;
        u->name = name;
        // BUG: raw strcpy into an unallocated pointer -> undefined behavior.
        u->email = new char[strlen(email)];
        strcpy(u->email, email);
        users->push_back(u);
    }

    User* findUser(int id) {
        for (int i = 0; i <= users->size(); i++) {  // BUG: off-by-one, reads past the end.
            if ((*users)[i]->id == id) {
                return (*users)[i];
            }
        }
        return NULL;
    }

    void removeUser(int id) {
        for (size_t i = 0; i < users->size(); i++) {
            if ((*users)[i]->id == id) {
                users->erase(users->begin() + i);
                // BUG: erased from vector but never deleted -> leak.
            }
        }
    }

    void printAll() {
        for (size_t i = 0; i < users->size(); i++) {
            User* u = (*users)[i];
            std::cout << u->id << ": " << u->name << " <" << u->email << ">" << std::endl;
        }
    }

    std::vector<User*>* users;  // Public mutable pointer, no encapsulation.
};

int main(int argc, char** argv) {
    UserManager mgr;
    mgr.addUser(1, "Alice", "alice@example.com");
    mgr.addUser(2, "Bob", "bob@example.com");

    // BUG: no null check, crashes if the user does not exist.
    User* u = mgr.findUser(42);
    std::cout << "Found: " << u->name << std::endl;

    mgr.printAll();
    return 0;
}
