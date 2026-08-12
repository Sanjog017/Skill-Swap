#include "registration.h"
#include "menu.h"
#include "validation.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Registration::Registration(Menu* menu) {
    this->menu = menu;
}

void Registration::registerUser() {
    menu->clearScreen();

    string name, username, password, confirm;

    // ask until full name is valid
    do {
        cout << "=== Register ===" << endl;
        cout << "Enter full name: ";
        getline(cin, name);

        // cancel if input ends (Ctrl+D / end of file)
        if (cin.eof()) {
            return;
        }

        if (!Validation::isValidName(name)) {
            cout << "Name cannot be empty." << endl;
        }
    } while (!Validation::isValidName(name));

    // ask until username is valid and not taken
    do {
        cout << "Enter username: ";
        getline(cin, username);

        if (cin.eof()) {
            return;
        }

        if (!Validation::isValidUsername(username)) {
            cout << "Username cannot be empty or contain spaces." << endl;
        }
        else if (fileManager.usernameExists(username)) {
            cout << "Username already exists. Choose another." << endl;
        }
    } while (!Validation::isValidUsername(username) || fileManager.usernameExists(username));

    // ask until password is valid and confirmed
    do {
        cout << "Enter password: ";
        password = Validation::readPassword();

        if (cin.eof()) {
            return;
        }

        if (!Validation::isValidPassword(password)) {
            cout << "Password cannot be empty." << endl;
        }
        else {
            cout << "Confirm password: ";
            confirm = Validation::readPassword();

            if (cin.eof()) {
                return;
            }

            if (password != confirm) {
                cout << "Passwords do not match. Try again." << endl;
            }
        }
    } while (!Validation::isValidPassword(password) || password != confirm);

    // next available id is biggest id + 1
    vector<User> users = fileManager.loadUsers();
    int nextId = 1;
    for (User& u : users) {
        if (u.getId() >= nextId) {
            nextId = u.getId() + 1;
        }
    }

    // admin is separate (admin.txt), so new users are always "user"
    User newUser(nextId, name, username, password, "user");
    fileManager.saveUser(newUser);

    cout << "Registration successful!" << endl;
    cout << "Press Enter to continue...";
    getline(cin, username);
}
