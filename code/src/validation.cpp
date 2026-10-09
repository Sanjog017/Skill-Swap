#include "validation.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

namespace skillswap {

// names may repeat, but they cannot be empty
bool Validation::isValidName(const string& name) {
    return name != "";
}

// usernames must be unique, so no spaces are allowed (and cannot be empty)
bool Validation::isValidUsername(const string& username) {
    if (username == "") return false;
    for (int i = 0; i < (int)username.length(); i++) {
        if (username[i] == ' ') {
            return false;
        }
    }
    return true;
}

// passwords cannot be empty
bool Validation::isValidPassword(const string& password) {
    return password != "";
}

// skill names cannot contain commas (commas would break the data file)
bool Validation::isValidSkill(const string& name) {
    if (name == "") return false;
    for (int i = 0; i < (int)name.length(); i++) {
        if (name[i] == ',') {
            return false;
        }
    }
    return true;
}

// programme (the course being studied) cannot be empty or contain commas
bool Validation::isValidProgramme(const string& programme) {
    if (programme == "") return false;
    for (int i = 0; i < (int)programme.length(); i++) {
        if (programme[i] == ',') {
            return false;
        }
    }
    return true;
}

// semester cannot be empty and cannot contain commas
bool Validation::isValidSemester(const string& semester) {
    if (semester == "") return false;
    for (int i = 0; i < (int)semester.length(); i++) {
        if (semester[i] == ',') {
            return false;
        }
    }
    return true;
}

// a simple email check: has @ and a dot, no spaces or commas
bool Validation::isValidEmail(const string& email) {
    if (email == "") return false;
    bool hasAt = false;
    bool hasDot = false;
    for (int i = 0; i < (int)email.length(); i++) {
        char c = email[i];
        if (c == ' ' || c == ',') {
            return false;
        }
        if (c == '@') hasAt = true;
        if (c == '.') hasDot = true;
    }
    return hasAt && hasDot;
}

// projects are optional (empty is fine), but cannot contain commas
bool Validation::isValidProjects(const string& projects) {
    if (projects == "") return true;
    for (int i = 0; i < (int)projects.length(); i++) {
        if (projects[i] == ',') {
            return false;
        }
    }
    return true;
}

// reads a password and shows * for every character typed
string Validation::readPassword() {
    string password = "";
    // show the prompt now — we read the fd directly, not std::cin,
    // so std::cout is not auto-flushed before the first key is pressed
    cout.flush();
#ifdef _WIN32
    char c;
    while (true) {
        c = (char)_getch();
        if (c == '\r') break;
        if (c == '\b' && password.length() > 0) {
            password.pop_back();
            cout << "\b \b";
        }
        else if (c != '\b') {
            password += c;
            cout << "*";
        }
    }
    cout << "\n";
#else
    struct termios oldSettings, newSettings;
    // terminal input (with echo off, one key at a time)
    if (tcgetattr(STDIN_FILENO, &oldSettings) == 0) {
        newSettings = oldSettings;
        newSettings.c_lflag &= (~ICANON);
        newSettings.c_lflag &= (~ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

        char c;
        while (true) {
            if (read(STDIN_FILENO, &c, 1) != 1) break;
            if (c == '\n') break;
            if (c == '\b' || c == 127) {
                if (password.length() > 0) {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                password += c;
                cout << "*";
            }
            cout.flush();
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
        cout << "\n";
    }
    else {
        // piped input / no terminal — simple fallback
        getline(cin, password);
    }
#endif
    return password;
}

} // namespace skillswap