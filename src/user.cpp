#include "user.h"
#include <string>

using namespace std;

User::User(int id, string name, string username, string password, string role) {
    this->id = id;
    this->name = name;
    this->username = username;
    this->password = password;
    this->role = role;
}

int User::getId() const {
    return id;
}

string User::getName() const {
    return name;
}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

string User::getRole() const {
    return role;
}
