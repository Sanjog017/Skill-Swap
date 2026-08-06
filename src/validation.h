// validation.h
// DECLARES the input-checking functions.
// These return true if the input is OK, false if it is bad.
// The actual code is in validation.cpp.

#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

// returns true if the name is not empty
bool isValidName(std::string name);

// returns true if the username is not empty and has no spaces
bool isValidUsername(std::string username);

// returns true if the password is not empty
bool isValidPassword(std::string password);

#endif
