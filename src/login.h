#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include "user.h"
#include "filemanager.h"

class Menu;

class Login {
public:
    Login(Menu* menu);
    bool loginUser();
    void logout();
    bool isAdminLoggedIn();
    bool isUserLoggedIn();
    std::string getCurrentUsername();
    int getCurrentUserId();

private:
    bool adminLogin(std::string username, std::string password);

    Menu* menu;
    FileManager fileManager;
    User* currentUser;      // nullptr when no user is logged in
    bool adminLoggedIn;
};

#endif
