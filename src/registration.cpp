// registration.cpp
// IMPLEMENTS the registration flow:
//   1. ask for Full Name
//   2. ask for Username (must be new, no spaces)
//   3. ask for Password
//   4. save the new user to users.txt
// A "do...while" loop is used so the question is ALWAYS asked at least
// once, and is re-asked whenever the answer is bad.

#include "registration.h"
#include "user.h"          // to create a User object
#include "filemanager.h"   // to check usernames and save the user
#include "validation.h"    // to check that input is valid
#include <iostream>
#include <string>

using namespace std;

void registerUser()
{
    // variables that will hold what the user types
    string name;
    string username;
    string password;

    cout << "\n--- Registration ---\n";

    // STEP 1: Full Name (cannot be empty)
    do
    {
        cout << "Full Name: ";
        getline(cin, name);                 // read a whole line of text

        if (!isValidName(name))             // invalid = empty
        {
            cout << "Name cannot be empty.\n";
        }
    } while (!isValidName(name));           // repeat while the name is still bad

    // STEP 2: Username (cannot be empty, no spaces, must be new)
    do
    {
        cout << "Username: ";
        getline(cin, username);

        if (!isValidUsername(username))     // empty or has a space
        {
            cout << "Username cannot be empty or contain spaces.\n";
        }
        else if (usernameExists(username))  // check the file for a match
        {
            cout << "Username already exists. Please choose another.\n";
            username = "";                  // clear it so the loop repeats
        }
    } while (!isValidUsername(username));

    // STEP 3: Password (cannot be empty)
    do
    {
        cout << "Password: ";
        getline(cin, password);

        if (!isValidPassword(password))
        {
            cout << "Password cannot be empty.\n";
        }
    } while (!isValidPassword(password));

    // STEP 4: pack everything into a User object and save it to the file
    User newUser(name, username, password);
    saveUser(newUser);

    cout << "\nRegistration Successful.\n";
    cout << "Press Enter to continue...";   // pause so the message is readable
    cin.get();                              // wait for the Enter key
}
