#ifndef LOGIN_H
#define LOGIN_H

#include "namespace.h"
#include <string>

namespace skillswap {

// Login — authentication and the current session.
// Keeps the logged-in user's info so the Menu can build the right Account.
class Login {
public:
    Login();                   // starts logged out
    bool loginUser();          // asks admin/user, then checks that file
    void logout();             // clears the session
    bool isLoggedIn() const;   // is anyone logged in?
    bool isAdmin() const;      // is the admin logged in?

    // getters (inline)
    int getUserId() const { return userId; }
    std::string getName() const { return name; }
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }

private:
    bool loggedIn;
    bool adminLogIn;
    int userId;
    std::string name;
    std::string username;
    std::string password;
};

} // namespace skillswap

#endif