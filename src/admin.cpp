#include "admin.h"
#include "filemanager.h"
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

// prints one line of a box (fixed width, pads with spaces)
void Admin::printBoxLine(string text, int width) {
    cout << "  | " << text;
    for (int i = 0; i < (int)(width - text.length()); i++) {
        cout << " ";
    }
    cout << " |\n";
}

// shows the admin menu — this is the overridden version of Account::displayMenu()
void Admin::displayMenu() {
    string choice;

    while (true) {
        clearScreen();

        string header = "=== Admin Menu (@admin) ===";

        cout << "\n";
        cout << "  +----------------------------------------+\n";
        printBoxLine(header, 40);
        cout << "  |                                        |\n";
        printBoxLine("   1. View All Users", 40);
        printBoxLine("   2. Delete User", 40);
        printBoxLine("   3. Generate Report", 40);
        printBoxLine("   4. Logout", 40);
        cout << "  |                                        |\n";
        cout << "  +----------------------------------------+\n";
        cout << "\n";
        cout << "  Enter choice: ";

        if (!getline(cin, choice)) {
            return;
        }

        if (choice == "1") {
            viewAllUsers();
        }
        else if (choice == "2") {
            deleteUser();
        }
        else if (choice == "3") {
            generateReport();
        }
        else if (choice == "4") {
            cout << "\n  Logged out!" << endl;
            return;
        }
        else {
            cout << "  Invalid choice. Try again." << endl;
            pause();
        }
    }
}

// lists every user with their full profile (admin sees everything)
void Admin::viewAllUsers() {
    clearScreen();
    cout << "  === All Users ===\n\n";

    try {
        FileManager fm;
        vector<User> users = fm.loadUsers();

        if (users.size() == 0) {
            cout << "  No users yet.\n";
            pause();
            return;
        }

        for (int i = 0; i < (int)users.size(); i++) {
            const User& u = users[i];
            cout << "  " << u.getId() << ". @" << u.getUsername() << " — " << u.getName() << "\n";
            cout << "     Programme: " << (u.getProgramme() == "" ? "-" : u.getProgramme()) << "\n";
            cout << "     Semester:  " << (u.getSemester() == "" ? "-" : u.getSemester()) << "\n";
            cout << "     Projects:  " << (u.getProjects() == "" ? "-" : u.getProjects()) << "\n";
            cout << "     Email:    " << (u.getEmail() == "" ? "-" : u.getEmail()) << "\n";
            cout << "     Teaches:  " << skillList(u.getId(), TEACH) << "\n";
            cout << "     Learns:   " << skillList(u.getId(), LEARN) << "\n";
            cout << "\n";
        }
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
    }
    pause();
}

// deletes one user by id
void Admin::deleteUser() {
    clearScreen();
    cout << "  === Delete User ===\n\n";

    try {
        FileManager fm;
        vector<User> users = fm.loadUsers();

        if (users.size() == 0) {
            cout << "  No users to delete.\n";
            pause();
            return;
        }

        for (int i = 0; i < (int)users.size(); i++) {
            cout << "  " << users[i].getId() << ". @" << users[i].getUsername()
                 << " — " << users[i].getName() << "\n";
        }

        cout << "\n  User id to delete (or 0 to cancel): ";
        string input;
        if (!getline(cin, input)) return;
        if (input == "0" || input == "") return;

        int id;
        try {
            id = stoi(input);
        }
        catch (...) {
            cout << "  Invalid number.\n";
            pause();
            return;
        }

        bool found = false;
        for (int i = 0; i < (int)users.size(); i++) {
            if (users[i].getId() == id) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "  No user with that id.\n";
            pause();
            return;
        }

        fm.deleteUser(id);
        cout << "  User deleted (along with their skills and requests).\n";
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
    }
    pause();
}

// counts of users, skills and requests
void Admin::generateReport() {
    clearScreen();
    cout << "  === Report ===\n\n";

    try {
        FileManager fm;
        vector<User> users = fm.loadUsers();
        vector<Skill> skills = fm.loadSkills();
        vector<SkillRequest> requests = fm.loadRequests();

        int teach = 0, learn = 0;
        for (int i = 0; i < (int)skills.size(); i++) {
            if (skills[i].getType() == TEACH) teach++;
            else learn++;
        }

        int pending = 0, accepted = 0, rejected = 0;
        for (int i = 0; i < (int)requests.size(); i++) {
            RequestStatus s = requests[i].getStatus();
            if (s == PENDING) pending++;
            else if (s == ACCEPTED) accepted++;
            else rejected++;
        }

        cout << "  Users:                 " << users.size() << "\n";
        cout << "  Teach skills:          " << teach << "\n";
        cout << "  Learn skills:          " << learn << "\n";
        cout << "  Pending requests:      " << pending << "\n";
        cout << "  Accepted requests:     " << accepted << "\n";
        cout << "  Rejected requests:     " << rejected << "\n";
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
    }
    pause();
}

// builds a comma-separated list of a user's teach (or learn) skills
string Admin::skillList(int userId, SkillType type) {
    string result = "";
    try {
        FileManager fm;
        vector<Skill> skills = fm.skillsOf(userId);
        for (int i = 0; i < (int)skills.size(); i++) {
            if (skills[i].getType() == type) {
                if (result != "") result += ", ";
                result += skills[i].getName();
            }
        }
    }
    catch (FileException e) {
        result = "";
    }
    if (result == "") result = "-";
    return result;
}

} // namespace skillswap