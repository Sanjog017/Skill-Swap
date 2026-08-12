#include "menu.h"
#include <iostream>
#include <string>

using namespace std;

void Menu::clearScreen() {
    // ANSI escape code clears the console
    cout << "\033[2J\033[1;1H";
}

void Menu::showMainMenu() {
    string choice;

    while (true) {
        clearScreen();

        cout << "=== Skill Swap ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Login is not implemented yet." << endl;
        }
        else if (choice == "2") {
            cout << "Register is not implemented yet." << endl;
        }
        else if (choice == "3") {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }

        cout << "Press Enter to continue...";
        getline(cin, choice);
    }
}
