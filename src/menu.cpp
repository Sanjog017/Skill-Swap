#include "menu.h"
#include "account.h"
#include "user.h"
#include "admin.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

namespace skillswap {

Menu::Menu() {
    currentAccount = nullptr;
}

// deletes the logged-in account if any (uses delete — works because ~Account is virtual)
Menu::~Menu() {
    delete currentAccount;
}

// clears the terminal screen (works on Windows and Linux)
void Menu::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// waits for the user to press Enter before continuing
void Menu::pause() {
    cout << "\nPress Enter to continue...";
    string dummy;
    getline(cin, dummy);
}

// shows the main menu and handles login/register/exit choices
void Menu::showMainMenu() {
    string choice;

    while (true) {
        clearScreen();

        cout << "\n";
        cout << "  +--------------------------------+\n";
        cout << "  |        === Skill Swap ===      |\n";
        cout << "  |                                |\n";
        cout << "  |        1. Login                |\n";
        cout << "  |        2. Register             |\n";
        cout << "  |        3. Exit                 |\n";
        cout << "  |                                |\n";
        cout << "  +--------------------------------+\n";
        cout << "\n";
        cout << "  Enter choice: ";

        if (!getline(cin, choice)) {
            break;
        }

        if (choice == "1") {
            // --- polymorphism demo ---
            // for now, ask user to pick "user" or "admin" to simulate login
            // later phases will do real credential checking
            clearScreen();
            cout << "\n  Login as:\n";
            cout << "  1. User\n";
            cout << "  2. Admin\n";
            cout << "\n  Enter choice: ";

            string roleChoice;
            getline(cin, roleChoice);

            if (roleChoice == "1") {
                // create a User object — stored as Account* (polymorphism)
                currentAccount = new User(1, "Test User", "testuser", "pass123");
                cout << "\n  Login successful!" << endl;
                pause();

                // virtual function call — runs User::displayMenu(), not Account's
                currentAccount->displayMenu();

                delete currentAccount;
                currentAccount = nullptr;
            }
            else if (roleChoice == "2") {
                // create an Admin object — stored as Account* (polymorphism)
                currentAccount = new Admin(1, "Admin", "admin", "password");
                cout << "\n  Admin login successful!" << endl;
                pause();

                // virtual function call — runs Admin::displayMenu(), not Account's
                currentAccount->displayMenu();

                delete currentAccount;
                currentAccount = nullptr;
            }
            else {
                cout << "\n  Invalid choice." << endl;
                pause();
            }
        }
        else if (choice == "2") {
            cout << "\n  Register coming soon..." << endl;
            pause();
        }
        else if (choice == "3") {
            cout << "\n  Goodbye!" << endl;
            break;
        }
        else {
            cout << "\n  Invalid choice. Try again." << endl;
            pause();
        }
    }
}

} // namespace skillswap
