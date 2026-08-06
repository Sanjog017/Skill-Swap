// main.cpp
// The program always starts running here (from the top of main).
// Its only job: hand control over to the menu, then stop when done.

#include "menu.h"      // brings in the showMainMenu() function so we can call it

int main()
{
    // start the app by showing the main menu
    // this function only returns when the user chooses Exit
    showMainMenu();

    return 0;          // 0 means "the program finished without errors"
}
