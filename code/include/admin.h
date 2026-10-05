#ifndef ADMIN_H
#define ADMIN_H

#include "account.h"
#include "skill.h"

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
    void printBoxLine(std::string text, int width);   // prints one box line

    void viewAllUsers();    // every user with their full profile
    void deleteUser();      // remove a user (and their skills + requests)
    void generateReport();  // counts of users / skills / requests

    // builds "guitar, python" from a user's teach (or learn) skills
    std::string skillList(int userId, SkillType type);
};

} // namespace skillswap

#endif