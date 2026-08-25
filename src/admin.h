#ifndef ADMIN_H
#define ADMIN_H

#include "account.h"

namespace skillswap {

// Admin inherits from Account — has extra privileges like deleting users
class Admin : public Account {
public:
    // constructor — passes everything up to Account
    Admin(int id, std::string name, std::string username,
          std::string password, std::string role = "admin");

    // overrides Account's pure virtual function
    void displayMenu() override;

private:
    void clearScreen();     // clears the terminal
    void pause();           // waits for Enter key
};

} // namespace skillswap

#endif
