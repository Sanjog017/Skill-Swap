#include "menu.h"
#include "user.h"
#include "admin.h"
#include "login.h"
#include "registration.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

namespace skillswap {

Menu::Menu() {
    login = new Login();
    registerPage = new Registration();
    currentAccount = nullptr;
}

// deletes the pages and the logged-in account if any
Menu::~Menu() {
    delete login;
    delete registerPage;
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

// the main loop: Login / Register / Exit
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
            break;   // EOF (Ctrl+D) — quit safely
        }

        if (choice == "1") {
            clearScreen();
            bool ok = login->loginUser();

            // polymorphism — build the right kind of account under an Account*
            if (ok && login->isAdmin()) {
                currentAccount = new Admin(0, "Admin", login->getUsername(),
                                           login->getPassword());
            }
            else if (ok) {
                currentAccount = new User(login->getUserId(), login->getName(),
                                          login->getUsername(), login->getPassword());
            }

            if (currentAccount != nullptr) {
                cout << "\n  Login successful! Welcome back, @"
                     << currentAccount->getUsername() << "!\n";
                pause();

                // virtual call — runs User::displayMenu() or Admin::displayMenu()
                currentAccount->displayMenu();

                delete currentAccount;   // log out
                currentAccount = nullptr;
                login->logout();
            }
            else {
                cout << "\n  Invalid username or password.\n";
                pause();
            }
        }
        else if (choice == "2") {
            clearScreen();
            registerPage->registerUser();
            pause();
        }
        else if (choice == "3") {
            cout << "\n  Goodbye!" << endl;
            break;
        }
        else {
            cout << "  Invalid choice. Try again." << endl;
            pause();
        }
    }
}

} // namespace skillswap