// filemanager.h
// DECLARES the file-related functions.
// This module is the ONLY place that touches users.txt.
// If we ever change the file format, only this module changes.

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "user.h"   // needed because saveUser() takes a User object

// returns true if someone already has this username in users.txt
bool usernameExists(std::string username);

// writes one new user into users.txt (at the end of the file)
void saveUser(const User& user);

#endif
