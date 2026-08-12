#include "validation.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

bool Validation::isValidName(string name) {
    return !name.empty();
}

bool Validation::isValidUsername(string username) {
    if (username.empty()) {
        return false;
    }
    // no spaces allowed in username
    for (char c : username) {
        if (c == ' ') {
            return false;
        }
    }
    return true;
}

bool Validation::isValidPassword(string password) {
    return !password.empty();
}

// reads password without showing it on screen (shows * instead)
string Validation::readPassword() {
    string password;

#ifdef _WIN32
    int ch;
    while (true) {
        ch = _getch();
        if (ch == '\r') {
            break;
        }
        else if (ch == '\b') {
            // backspace removes last *
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;

#else
    termios oldt, newt;

    // terminal settings can only change on a real console
    if (tcgetattr(STDIN_FILENO, &oldt) == 0) {
        // turn off echo and line mode so we can print * ourselves
        newt = oldt;
        newt.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        int ch;
        while (true) {
            ch = getchar();
            if (ch == '\n' || ch == '\r') {
                break;
            }
            else if (ch == 127 || ch == 8) {
                // backspace removes last *
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else if (ch == EOF) {
                break;
            }
            else {
                password += ch;
                cout << '*' << flush;
            }
        }

        // restore terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        cout << endl;
    }
    else {
        // not a real console (piped input) - just read the line
        getline(cin, password);
    }
#endif

    return password;
}
