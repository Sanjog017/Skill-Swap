#ifndef MENU_H
#define MENU_H

#include "namespace.h"

namespace skillswap {

class Menu {
public:
    Menu();             // creates menu components
    ~Menu();            // cleans up menu components
    void showMainMenu();    // displays login/register/exit loop

private:
    void clearScreen();     // clears the terminal
    void pause();           // waits for Enter key

    Account* currentAccount;    // polymorphism — points to User or Admin
};

} // namespace skillswap

#endif
