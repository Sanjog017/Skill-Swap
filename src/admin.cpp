#include "admin.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

namespace skillswap {

// default argument role="admin" is defined in the header
Admin::Admin(int id, string name, string username, string password, string role)
    : Account(id, name, username, password, role) {
    // all work done by Account constructor above
}

// clears the terminal screen
void Admin::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// waits for the user to press Enter before continuing
void Admin::pause() {
    cout << "\nPress Enter to continue...";
    string dummy;
    getline(cin, dummy);
}

// shows the admin menu — this is the overridden version of Account::displayMenu()
void Admin::displayMenu() {
    string choice;

    while (true) {
        clearScreen();

        string header = "=== Admin Menu (@" + username + ") ===";

        cout << "\n";
        cout << "  +--------------------------------------+\n";
        cout << "  | " << header;
        for (int i = 0; i < (int)(38 - header.length()); i++) cout << " ";
        cout << " |\n";
        cout << "  |                                      |\n";
        cout << "  |   1. View All Users                  |\n";
        cout << "  |   2. Delete User                     |\n";
        cout << "  |   3. Generate Report                 |\n";
        cout << "  |   4. Logout                          |\n";
        cout << "  |                                      |\n";
        cout << "  +--------------------------------------+\n";
        cout << "\n";
        cout << "  Enter choice: ";

        if (!getline(cin, choice)) {
            return;
        }

        if (choice == "1") {
            cout << "\n  View All Users coming soon..." << endl;
            pause();
        }
        else if (choice == "2") {
            cout << "\n  Delete User coming soon..." << endl;
            pause();
        }
        else if (choice == "3") {
            cout << "\n  Generate Report coming soon..." << endl;
            pause();
        }
        else if (choice == "4") {
            cout << "\n  Logged out!" << endl;
            return;
        }
        else {
            cout << "\n  Invalid choice. Try again." << endl;
            pause();
        }
    }
}

} // namespace skillswap
