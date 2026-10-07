#include "login.h"
#include "validation.h"
#include "filemanager.h"
#include <iostream>

using namespace std;

namespace skillswap {

Login::Login() {
    loggedIn = false;
    adminLogIn = false;
    userId = -1;
    name = "";
    username = "";
    password = "";
}

// asks who is logging in, then checks that file only
bool Login::loginUser() {
    string accountType;

    cout << "\n  === Login ===\n\n";

    // step 1 — admin or user?
    while (true) {
        cout << "  Login as (1. Admin / 2. User): ";
        if (!getline(cin, accountType)) return false;   // EOF

        if (accountType == "1" || accountType == "2") break;
        cout << "  Invalid choice. Try again." << endl;
    }

    bool loginAsAdmin = (accountType == "1");

    // step 2 — credentials
    cout << "\n  Username: ";
    if (!getline(cin, username)) return false;

    cout << "  Password: ";
    password = Validation::readPassword();

    try {
        FileManager fm;

        // admin has its own small file
        if (loginAsAdmin) {
            if (fm.adminExists(username, password)) {
                loggedIn = true;
                adminLogIn = true;
                return true;
            }
            return false;
        }

        // regular users live in users.txt
        vector<User> users = fm.loadUsers();
        for (int i = 0; i < (int)users.size(); i++) {
            if (users[i].getUsername() == username &&
                users[i].getPassword() == password) {
                loggedIn = true;
                adminLogIn = false;
                userId = users[i].getId();
                name = users[i].getName();
                return true;
            }
        }
    }
    catch (FileException e) {
        cout << "\n  Error: " << e.message << "\n";
        return false;
    }
    return false;
}

// clears the session (called after the menu session ends)
void Login::logout() {
    loggedIn = false;
    adminLogIn = false;
    userId = -1;
    name = "";
    username = "";
    password = "";
}

bool Login::isLoggedIn() const {
    return loggedIn;
}

bool Login::isAdmin() const {
    return adminLogIn;
}

} // namespace skillswap