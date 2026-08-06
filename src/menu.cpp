// menu.cpp
// IMPLEMENTS the main menu:
//   it prints the options, reads the user's choice, and does the action.
//   after each action it loops back and shows the menu again,
//   until the user picks Exit.

#include "menu.h"
#include "registration.h"   // so we can call registerUser()
#include <iostream>
#include <string>

using namespace std;

// clears the console screen.
// "\033[2J\033[1;1H" is an ANSI escape code (a hidden command the
// terminal understands) that means "clear everything, cursor to top".
int clearscreen()
{
    cout << "\033[2J\033[1;1H";
    return 0;
}

void showMainMenu()
{
    string choice;   // store the user's choice as text

    // infinite loop: it only stops when we hit "break" (the Exit case)
    while (true)
    {
        clearscreen();   // fresh screen for each menu

        cout << "Welcome to SkillSwap\n\n";
        cout << "Main Menu\n";
        cout << "[1] Login\n";
        cout << "[2] Register\n";
        cout << "[3] Exit\n\n";
        cout << "Enter your choice: ";
        getline(cin, choice);    // read the whole line of input

        if (choice == "1")
        {
            // Login is not built yet, so just say so and go back to menu
            cout << "\nLogin is not implemented yet.\n";
            cout << "Press Enter to continue...";
            cin.get();           // wait for Enter before clearing the screen
        }
        else if (choice == "2")
        {
            registerUser();      // run registration, then the loop restarts
        }
        else if (choice == "3")
        {
            cout << "\nGoodbye!\n";
            break;               // leave the while loop -> exit the program
        }
        else
        {
            // anything that is not 1, 2 or 3
            cout << "\nInvalid choice, try again.\n";
            cout << "Press Enter to continue...";
            cin.get();
        }
    }
}
