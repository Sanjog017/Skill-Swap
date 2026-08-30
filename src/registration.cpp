#include "registration.h"
#include "validation.h"
#include "user.h"
#include "filemanager.h"
#include <iostream>

using namespace std;

namespace skillswap {

// the whole registration flow — every field is checked before saving
void Registration::registerUser() {
    cout << "\n  === Register ===\n\n";

    // full name (may repeat, cannot be empty)
    string name;
    do {
        cout << "  Full name: ";
        if (!getline(cin, name)) return;
        if (!Validation::isValidName(name)) {
            cout << "  Name cannot be empty.\n";
        }
    } while (!Validation::isValidName(name));

    // username (no spaces + must be unique)
    string username;
    bool taken = true;
    do {
        cout << "  Username: ";
        if (!getline(cin, username)) return;
        if (!Validation::isValidUsername(username)) {
            cout << "  Username cannot have spaces.\n";
            taken = true;
        }
        else {
            try {
                taken = FileManager().usernameExists(username);
            }
            catch (FileException e) {
                cout << "  Error: " << e.message << "\n";
                return;
            }
            if (taken) {
                cout << "  That username is already taken.\n";
            }
        }
    } while (taken);

    // password + confirm (masked input)
    string password;
    string confirm;
    do {
        cout << "  Password: ";
        password = Validation::readPassword();
        cout << "  Confirm: ";
        confirm = Validation::readPassword();
        if (!Validation::isValidPassword(password)) {
            cout << "  Password cannot be empty.\n";
        }
        else if (password != confirm) {
            cout << "  Passwords do not match.\n";
        }
    } while (password == "" || password != confirm);

    // programme (the course they are studying — public profile info)
    string programme;
    do {
        cout << "  Programme (course, e.g. B.Tech CSE): ";
        if (!getline(cin, programme)) return;
        if (!Validation::isValidProgramme(programme)) {
            cout << "  Programme cannot be empty.\n";
        }
    } while (!Validation::isValidProgramme(programme));

    // semester (public profile info)
    string semester;
    do {
        cout << "  Semester (e.g. 3): ";
        if (!getline(cin, semester)) return;
        if (!Validation::isValidSemester(semester)) {
            cout << "  Semester cannot be empty.\n";
        }
    } while (!Validation::isValidSemester(semester));

    // email (contact — private, only shown to connections)
    string email;
    do {
        cout << "  Email: ";
        if (!getline(cin, email)) return;
        if (!Validation::isValidEmail(email)) {
            cout << "  That email looks wrong (need @ and a dot).\n";
        }
    } while (!Validation::isValidEmail(email));

    // projects (optional, shown publicly on the profile)
    string projects;
    do {
        cout << "  Projects (optional, separate with ;): ";
        if (!getline(cin, projects)) return;
        if (!Validation::isValidProjects(projects)) {
            cout << "  Projects cannot contain commas.\n";
        }
    } while (!Validation::isValidProjects(projects));

    try {
        FileManager fm;
        int id = fm.nextUserId();
        User u(id, name, username, password, "user", programme, semester, projects, email);
        fm.saveUser(u);
        cout << "\n  Registration successful! Welcome, " << username << "!\n";
    }
    catch (FileException e) {
        cout << "\n  Error: " << e.message << "\n";
    }
}

} // namespace skillswap