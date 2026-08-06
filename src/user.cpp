// user.cpp
// This file IMPLEMENTS the functions that user.h only declared.
// Here we actually write out what each function does.

#include "user.h"

// constructor: fills the object's 3 data members with the values given
User::User(std::string n, std::string u, std::string p)
{
    name = n;          // store the passed-in name into our member
    username = u;      // store the passed-in username
    password = p;      // store the passed-in password
}

// getter: just hands back the stored value
std::string User::getName() const
{
    return name;
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}
