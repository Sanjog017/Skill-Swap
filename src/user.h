#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(int id, std::string name, std::string username,
         std::string password, std::string role);

    int getId() const;
    std::string getName() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRole() const;

private:
    int id;
    std::string name;       // full name, e.g. "Sanjog Pathak"
    std::string username;   // unique login name, e.g. "sanjog017"
    std::string password;
    std::string role;
};

#endif
