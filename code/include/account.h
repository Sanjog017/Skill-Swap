#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "namespace.h"
#include <string>
#include <iostream>

namespace skillswap {

// Abstract base class — User and Admin inherit from this.
// Pure virtual function displayMenu() makes this abstract.
class Account {
public:
    // parameterized constructor
    Account(int id, std::string name, std::string username,
            std::string password, std::string role);

    // virtual destructor — needed so the right destructor runs when deleting via Account*
    virtual ~Account();

    // pure virtual function — each subclass must provide its own menu
    virtual void displayMenu() = 0;

    // getters (inline — defined right here in the header)
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getRole() const { return role; }

protected:
    // protected — accessible by derived classes (User, Admin) but not from outside
    int id;
    std::string name;
    std::string username;
    std::string password;
    std::string role;
};

} // namespace skillswap

#endif
