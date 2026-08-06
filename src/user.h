// user.h
// This file only DECLARES the User class: it says what data a user has
// and what functions it can do, but NOT how those functions work.
// The actual code lives in user.cpp.

#ifndef USER_H
#define USER_H

#include <string>

class User
{
    private:
        // data members: every User object will store these 3 strings
        std::string name;        // the person's real full name, e.g. "John Doe"
        std::string username;    // the login name, e.g. "john"
        std::string password;    // the secret password

    public:
        // constructor: a special function called automatically when we
        // create a User, e.g. User newUser(name, username, password);
        User(std::string n, std::string u, std::string p);

        // getters: functions that let other code READ a private value.
        // we make them "const" because reading should not change the object.
        std::string getName() const;
        std::string getUsername() const;
        std::string getPassword() const;
};

#endif // ends the include guard
