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

// asks for credentials and checks admin.txt first, then users.txt
bool Login::loginUser() {
    cout << "\n  === Login ===\n\n";

    cout << "  Username: ";
    if (!getline(cin, username)) return false;

    cout << "  Password: ";
    password = Validation::readPassword();

    try {
        FileManager fm;
        // admin has its own small file
        if (fm.adminExists(username, password)) {
            loggedIn = true;
            adminLogIn = true;
            return true;
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