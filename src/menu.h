#ifndef MENU_H
#define MENU_H

#include "namespace.h"
#include "account.h"

namespace skillswap {

class Menu {
public:
    Menu();             // creates the login and registration pages
    ~Menu();            // deletes them and the logged-in account (new/delete)
    void showMainMenu();    // displays login/register/exit loop

private:
    void clearScreen();     // clears the terminal
    void pause();           // waits for Enter key

    Login* login;               // handles login / session
    Registration* registerPage; // handles registration
    Account* currentAccount;    // polymorphism — points to User or Admin
};

} // namespace skillswap

#endif