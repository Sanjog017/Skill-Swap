#include "menu.h"
#include "registration.h"
#include "login.h"
#include "skill.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

Menu::Menu() {
    registration = new Registration(this);
    login = new Login(this);
    skillManager = new SkillManager(this);
}

void Menu::clearScreen() {
#ifdef _WIN32
    system("cls");       // Windows
#else
    system("clear");     // macOS / Linux
#endif
}

void Menu::pause() {
    cout << "Press Enter to continue...";
    string dummy;
    getline(cin, dummy);
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
        // exit if there is no more input (Ctrl+D / end of file)
        if (!getline(cin, choice)) {
            break;
        }

        if (choice == "1") {
            if (login->loginUser()) {
                if (login->isAdminLoggedIn()) {
                    cout << "Admin login successful!" << endl;
                    // admin menu will go here (Phase 8)
                    login->logout();
                }
                else {
                    cout << "Login successful! Welcome, @"
                         << login->getCurrentUsername() << endl;
                    pause();
                    // user menu (skills) until the user logs out
                    skillManager->showUserMenu(login);
                    login->logout();
                }
                pause();
            }
            else {
                cout << "Invalid username or password." << endl;
                pause();
            }
        }
        else if (choice == "2") {
            registration->registerUser();   // pauses by itself
        }
        else if (choice == "3") {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
            pause();
        }
    }
}
