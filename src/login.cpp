#include "login.h"
#include "menu.h"
#include "validation.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Login::Login(Menu* menu) {
    this->menu = menu;
    currentUser = nullptr;
    adminLoggedIn = false;
}

bool Login::adminLogin(string username, string password) {
    ifstream file("admin.txt");
    if (!file) {
        return false;
    }

    string line;
    getline(file, line);
    file.close();

    // admin.txt format: admin,password
    size_t comma = line.find(',');
    if (comma == string::npos) {
        return false;
    }

    string storedUser = line.substr(0, comma);
    string storedPass = line.substr(comma + 1);
    return storedUser == username && storedPass == password;
}

bool Login::loginUser() {
    menu->clearScreen();

    string username, password;

    cout << "=== Login ===" << endl;
    cout << "Enter username: ";
    getline(cin, username);
    if (cin.eof()) {
        return false;
    }

    cout << "Enter password: ";
    password = Validation::readPassword();
    if (cin.eof()) {
        return false;
    }

    // admin is stored separately in admin.txt
    if (adminLogin(username, password)) {
        adminLoggedIn = true;
        return true;
    }

    // check regular users in users.txt
    vector<User> users = fileManager.loadUsers();
    for (User& u : users) {
        if (u.getUsername() == username && u.getPassword() == password) {
            currentUser = new User(u);
            return true;
        }
    }

    return false;
}

void Login::logout() {
    delete currentUser;
    currentUser = nullptr;
    adminLoggedIn = false;
}

bool Login::isAdminLoggedIn() {
    return adminLoggedIn;
}

bool Login::isUserLoggedIn() {
    return currentUser != nullptr;
}

string Login::getCurrentUsername() {
    if (currentUser != nullptr) {
        return currentUser->getUsername();
    }
    return "";
}

int Login::getCurrentUserId() {
    if (currentUser != nullptr) {
        return currentUser->getId();
    }
    return -1;
}
