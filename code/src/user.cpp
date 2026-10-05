#include "user.h"
#include "filemanager.h"
#include "validation.h"
#include "skillrequest.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

namespace skillswap {

int User::nextId = 1;

// default constructor — an empty user (id -1 means "not found")
User::User() : Account(-1, "", "", "", "user") {
    programme = "";
    semester = "";
    projects = "";
    email = "";
}

// default argument role="user" is defined in the header
User::User(int id, string name, string username, string password, string role,
           string programme, string semester, string projects, string email)
    : Account(id, name, username, password, role) {
    this->programme = programme;
    this->semester = semester;
    this->projects = projects;
    this->email = email;
}

// copy constructor — copies the base class and our extra fields
User::User(const User& other) : Account(other) {
    programme = other.programme;
    semester = other.semester;
    projects = other.projects;
    email = other.email;
}

int User::getNextId() {
    return nextId;
}

// operator<< for printing a User
ostream& operator<<(ostream& out, const User& u) {
    out << "@" << u.username << " — " << u.name;
    return out;
}

// clears the terminal screen
void User::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// waits for the user to press Enter before continuing
void User::pause() {
    cout << "\nPress Enter to continue...";
    string dummy;
    getline(cin, dummy);
}

// prints one line of a box (fixed width, pads with spaces)
void User::printBoxLine(string text, int width) {
    cout << "  | " << text;
    for (int i = 0; i < (int)(width - text.length()); i++) {
        cout << " ";
    }
    cout << " |\n";
}

// shows the user menu — this is the overridden version of Account::displayMenu()
void User::displayMenu() {
    string choice;

    while (true) {
        clearScreen();

        string header = "=== User Menu (@" + username + ") ===";

        cout << "\n";
        cout << "  +----------------------------------------+\n";
        printBoxLine(header, 40);
        cout << "  |                                        |\n";
        printBoxLine("   1. My Profile", 40);
        printBoxLine("   2. Search People", 40);
        printBoxLine("   3. Requests", 40);
        printBoxLine("   4. My Connections", 40);
        printBoxLine("   5. Sent Requests", 40);
        printBoxLine("   6. Logout", 40);
        cout << "  |                                        |\n";
        cout << "  +----------------------------------------+\n";
        cout << "\n";
        cout << "  Enter choice: ";

        if (!getline(cin, choice)) {
            return;
        }

        if (choice == "1") {
            viewMyProfile();
        }
        else if (choice == "2") {
            searchPeople();
        }
        else if (choice == "3") {
            viewRequests();
        }
        else if (choice == "4") {
            viewConnections();
        }
        else if (choice == "5") {
            viewSentRequests();
        }
        else if (choice == "6") {
            cout << "\n  Logged out!" << endl;
            return;
        }
        else {
            cout << "  Invalid choice. Try again." << endl;
            pause();
        }
    }
}

// ============================ MY PROFILE ============================

// my own profile card with the edit options
void User::viewMyProfile() {
    string choice;

    while (true) {
        clearScreen();
        showProfile(getId());

        cout << "\n";
        cout << "  1. Add Teach Skill\n";
        cout << "  2. Add Learn Skill\n";
        cout << "  3. Remove Skill\n";
        cout << "  4. Edit Profile\n";
        cout << "  5. Back\n";
        cout << "\n  Enter choice: ";

        if (!getline(cin, choice)) {
            return;
        }

        if (choice == "1") {
            addSkill(TEACH);
        }
        else if (choice == "2") {
            addSkill(LEARN);
        }
        else if (choice == "3") {
            removeSkill();
        }
        else if (choice == "4") {
            editProfile();
        }
        else if (choice == "5") {
            return;
        }
        else {
            cout << "  Invalid choice." << endl;
            pause();
        }
    }
}

// adds a teach or learn skill to my profile
void User::addSkill(SkillType type) {
    string label = (type == TEACH) ? "Teach" : "Learn";

    clearScreen();
    cout << "  === Add " << label << " Skill ===\n\n";

    cout << "  Skill name: ";
    string name;
    if (!getline(cin, name)) return;

    try {
        FileManager fm;
        if (!Validation::isValidSkill(name)) {
            cout << "  Skill names cannot contain commas.\n";
        }
        else if (fm.skillExists(getId(), name)) {
            cout << "  You already have that skill.\n";
        }
        else {
            Skill s(getId(), name, type);
            fm.saveSkill(s);
            cout << "  Added \"" << name << "\" to your " << label << " list.\n";
        }
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
    }
    pause();
}

// removes one of my skills
void User::removeSkill() {
    clearScreen();
    cout << "  === Remove Skill ===\n\n";

    try {
        FileManager fm;
        vector<Skill> mine = fm.skillsOf(getId());

        if (mine.size() == 0) {
            cout << "  You have no skills to remove.\n";
            pause();
            return;
        }

        for (int i = 0; i < (int)mine.size(); i++) {
            string label = (mine[i].getType() == TEACH) ? "teach" : "learn";
            cout << "  " << (i + 1) << ". " << mine[i].getName() << " (" << label << ")\n";
        }

        cout << "\n  Number to remove (or 0 to cancel): ";
        string input;
        if (!getline(cin, input)) return;
        if (input == "0" || input == "") return;

        int index;
        try {
            index = stoi(input) - 1;
        }
        catch (...) {
            cout << "  Invalid number.\n";
            pause();
            return;
        }

        if (index < 0 || index >= (int)mine.size()) {
            cout << "  Invalid number.\n";
            pause();
            return;
        }

        fm.removeSkill(getId(), mine[index].getName());
        cout << "  Removed \"" << mine[index].getName() << "\".\n";
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
    }
    pause();
}

// changes semester / projects / email of my profile
void User::editProfile() {
    clearScreen();
    cout << "  === Edit Profile ===\n\n";

    try {
        FileManager fm;

        string programme;
        do {
            cout << "  Programme (course, e.g. B.Tech CSE): ";
            if (!getline(cin, programme)) return;
            if (!Validation::isValidProgramme(programme)) {
                cout << "  Programme cannot be empty.\n";
            }
        } while (!Validation::isValidProgramme(programme));

        string semester;
        do {
            cout << "  Semester (e.g. 3): ";
            if (!getline(cin, semester)) return;
            if (!Validation::isValidSemester(semester)) {
                cout << "  Semester cannot be empty.\n";
            }
        } while (!Validation::isValidSemester(semester));

        string email;
        do {
            cout << "  Email: ";
            if (!getline(cin, email)) return;
            if (!Validation::isValidEmail(email)) {
                cout << "  That email looks wrong (need @ and a dot).\n";
            }
        } while (!Validation::isValidEmail(email));

        string projects;
        do {
            cout << "  Projects (optional, separate with ;): ";
            if (!getline(cin, projects)) return;
            if (!Validation::isValidProjects(projects)) {
                cout << "  Projects cannot contain commas.\n";
            }
        } while (!Validation::isValidProjects(projects));

        fm.updateUserProfile(getId(), programme, semester, projects, email);
        cout << "\n  Profile updated!\n";
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
    }
    pause();
}

// ============================ SEARCH PEOPLE ============================

// search users who teach ANY of the skills typed
void User::searchPeople() {
    clearScreen();
    cout << "  === Search People ===\n\n";

    cout << "  Skills to match (comma separated, e.g. guitar, python): ";
    string input;
    if (!getline(cin, input)) return;

    vector<string> wanted = splitSkills(input);
    if (wanted.size() == 0) {
        cout << "\n  Please enter at least one skill.\n";
        pause();
        return;
    }

    try {
        FileManager fm;
        vector<Skill> all = fm.loadSkills();
        vector<User> users = fm.loadUsers();

        // collect ids of users who teach ANY of the wanted skills (not myself)
        vector<int> matches;
        for (int i = 0; i < (int)all.size(); i++) {
            if (all[i].getType() != TEACH) continue;
            if (all[i].getUserId() == getId()) continue;

            bool isWanted = false;
            for (int w = 0; w < (int)wanted.size(); w++) {
                if (all[i].getName() == wanted[w]) {
                    isWanted = true;
                    break;
                }
            }
            if (!isWanted) continue;

            bool alreadyThere = false;
            for (int m = 0; m < (int)matches.size(); m++) {
                if (matches[m] == all[i].getUserId()) {
                    alreadyThere = true;
                    break;
                }
            }
            if (!alreadyThere) {
                matches.push_back(all[i].getUserId());
            }
        }

        if (matches.size() == 0) {
            cout << "\n  No one teaches those skills yet.\n";
            pause();
            return;
        }

        cout << "\n  People who teach: ";
        for (int w = 0; w < (int)wanted.size(); w++) {
            if (w > 0) cout << ", ";
            cout << wanted[w];
        }
        cout << "\n\n";

        for (int i = 0; i < (int)matches.size(); i++) {
            User u(0, "", "", "");
            for (int j = 0; j < (int)users.size(); j++) {
                if (users[j].getId() == matches[i]) {
                    u = users[j];
                    break;
                }
            }
            cout << "  " << (i + 1) << ". @" << u.getUsername() << " — " << u.getName() << "\n";
            cout << "     Teaches: " << skillList(matches[i], TEACH) << "\n";
            cout << "\n";
        }

        cout << "  Open profile number (or 0 to go back): ";
        string pick;
        if (!getline(cin, pick)) return;
        if (pick == "0" || pick == "") return;

        int index;
        try {
            index = stoi(pick) - 1;
        }
        catch (...) {
            cout << "  Invalid number.\n";
            pause();
            return;
        }

        if (index < 0 || index >= (int)matches.size()) {
            cout << "  Invalid number.\n";
            pause();
            return;
        }

        openProfile(matches[index]);
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
        pause();
    }
}

// shows one full profile and lets the user send a request from there
void User::openProfile(int ownerId) {
    clearScreen();
    showProfile(ownerId);

    cout << "\n";
    if (ownerId == getId()) {
        cout << "  This is your own profile.\n";
        pause();
        return;
    }

    cout << "  1. Send Request\n";
    cout << "  2. Back\n";
    cout << "\n  Enter choice: ";

    string choice;
    if (!getline(cin, choice)) return;

    if (choice == "1") {
        sendRequest(ownerId);
    }
}

// sends a request to connect with another user
void User::sendRequest(int toId) {
    try {
        FileManager fm;
        if (toId == getId()) {
            cout << "  You cannot send a request to yourself.\n";
        }
        else if (fm.areConnected(getId(), toId)) {
            cout << "  You are already connected.\n";
        }
        else if (fm.pendingExists(toId, getId())) {
            cout << "  That person already sent you a request — reply from your Requests screen.\n";
        }
        else if (fm.pendingExists(getId(), toId)) {
            cout << "  You already sent a request to this person.\n";
        }
        else {
            SkillRequest r(fm.nextRequestId(), getId(), toId, PENDING);
            fm.saveRequest(r);
            cout << "  Request sent!\n";
        }
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
    }
    pause();
}

// ============================ REQUESTS ============================

// my incoming pending requests — drill into the sender's profile to accept/reject
void User::viewRequests() {
    while (true) {
        clearScreen();
        cout << "  === Requests ===\n\n";

        try {
            FileManager fm;
            vector<SkillRequest> all = fm.loadRequests();

            // ids of requests addressed to me that are still pending
            vector<int> pendingIds;
            for (int i = 0; i < (int)all.size(); i++) {
                if (all[i].getToUser() == getId() && all[i].getStatus() == PENDING) {
                    pendingIds.push_back(all[i].getId());
                }
            }

            if (pendingIds.size() == 0) {
                cout << "  No pending requests.\n";
                pause();
                return;
            }

            for (int i = 0; i < (int)pendingIds.size(); i++) {
                int from = -1;
                for (int j = 0; j < (int)all.size(); j++) {
                    if (all[j].getId() == pendingIds[i]) {
                        from = all[j].getFromUser();
                        break;
                    }
                }
                User sender = fm.getUserById(from);
                string prog = sender.getProgramme();
                if (prog == "") prog = "-";
                string sem = sender.getSemester();
                if (sem == "") sem = "-";

                cout << "  " << (i + 1) << ". Request #" << pendingIds[i]
                     << " from @" << sender.getUsername() << "\n";
                cout << "     Programme: " << prog << "\n";
                cout << "     Semester:  " << sem << "\n";
                cout << "\n";
            }

            cout << "  Open request number (or 0 to go back): ";
            string pick;
            if (!getline(cin, pick)) return;
            if (pick == "0" || pick == "") return;

            int index;
            try {
                index = stoi(pick) - 1;
            }
            catch (...) {
                cout << "  Invalid number.\n";
                pause();
                continue;
            }
            if (index < 0 || index >= (int)pendingIds.size()) {
                cout << "  Invalid number.\n";
                pause();
                continue;
            }

            int reqId = pendingIds[index];
            int from = -1;
            for (int j = 0; j < (int)all.size(); j++) {
                if (all[j].getId() == reqId) {
                    from = all[j].getFromUser();
                    break;
                }
            }
            User sender = fm.getUserById(from);

            // drill in — show the sender's full profile, then accept/reject
            clearScreen();
            cout << "  === Request #" << reqId << " from @" << sender.getUsername() << " ===\n";
            showProfile(from);

            cout << "\n";
            cout << "  1. Accept\n";
            cout << "  2. Reject\n";
            cout << "  3. Back\n";
            cout << "\n  Enter choice: ";

            string choice;
            if (!getline(cin, choice)) return;

            if (choice == "1") {
                fm.updateRequestStatus(reqId, ACCEPTED);
                cout << "\n  Request accepted! @" << sender.getUsername()
                     << " is now your connection.\n";
                pause();
                continue;   // refresh the list
            }
            else if (choice == "2") {
                fm.updateRequestStatus(reqId, REJECTED);
                cout << "\n  Request rejected.\n";
                pause();
                continue;   // refresh the list
            }
        }
        catch (FileException e) {
            cout << "  Error: " << e.message << "\n";
            pause();
        }
    }
}

// ============================ CONNECTIONS ============================

// the people I am connected with — their profiles show contact info
void User::viewConnections() {
    while (true) {
        clearScreen();
        cout << "  === My Connections ===\n\n";

        try {
            FileManager fm;
            vector<SkillRequest> all = fm.loadRequests();

            // ids of the OTHER person in every accepted request
            vector<int> peerIds;
            for (int i = 0; i < (int)all.size(); i++) {
                if (all[i].getStatus() != ACCEPTED) continue;
                int peer = (all[i].getFromUser() == getId()) ? all[i].getToUser() : all[i].getFromUser();
                bool alreadyThere = false;
                for (int j = 0; j < (int)peerIds.size(); j++) {
                    if (peerIds[j] == peer) {
                        alreadyThere = true;
                        break;
                    }
                }
                if (!alreadyThere) {
                    peerIds.push_back(peer);
                }
            }

            if (peerIds.size() == 0) {
                cout << "  No connections yet. Send a request from Search People.\n";
                pause();
                return;
            }

            for (int i = 0; i < (int)peerIds.size(); i++) {
                User peer = fm.getUserById(peerIds[i]);
                cout << "  " << (i + 1) << ". @" << peer.getUsername() << " — " << peer.getName() << "\n";
            }

            cout << "\n  Open profile number (or 0 to go back): ";
            string pick;
            if (!getline(cin, pick)) return;
            if (pick == "0" || pick == "") return;

            int index;
            try {
                index = stoi(pick) - 1;
            }
            catch (...) {
                cout << "  Invalid number.\n";
                pause();
                continue;
            }
            if (index < 0 || index >= (int)peerIds.size()) {
                cout << "  Invalid number.\n";
                pause();
                continue;
            }

            clearScreen();
            showProfile(peerIds[index]);   // email is visible (we are connected)
            pause();
        }
        catch (FileException e) {
            cout << "  Error: " << e.message << "\n";
            pause();
        }
    }
}

// the requests I sent, with their status
void User::viewSentRequests() {
    clearScreen();
    cout << "  === Sent Requests ===\n\n";

    try {
        FileManager fm;
        vector<SkillRequest> all = fm.loadRequests();

        int shown = 0;
        for (int i = 0; i < (int)all.size(); i++) {
            if (all[i].getFromUser() != getId()) continue;

            User target = fm.getUserById(all[i].getToUser());
            string status = (all[i].getStatus() == PENDING)  ? "pending"
                          : (all[i].getStatus() == ACCEPTED) ? "accepted"
                          : "rejected";

            cout << "  Request #" << all[i].getId() << " to @"
                 << target.getUsername() << " — " << status << "\n";
            shown++;
        }

        if (shown == 0) {
            cout << "  You have not sent any requests.\n";
        }
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
    }
    pause();
}

// ============================ PROFILE PRIVACY ============================

// prints one user's profile card.
// Everything is public except the email — that is only shown to
// the owner themselves or to a connection.
void User::showProfile(int ownerId) {
    try {
        FileManager fm;
        User owner = fm.getUserById(ownerId);
        bool canSeeEmail = (ownerId == getId()) || fm.areConnected(ownerId, getId());

        cout << "\n";
        cout << "  === Profile: @" << owner.getUsername() << " ===\n";
        cout << "  Name:      " << owner.getName() << "\n";
        cout << "  Username:  @" << owner.getUsername() << "\n";
        cout << "  Programme: " << (owner.getProgramme() == "" ? "-" : owner.getProgramme()) << "\n";
        cout << "  Semester:  " << (owner.getSemester() == "" ? "-" : owner.getSemester()) << "\n";
        cout << "  Projects:  " << (owner.getProjects() == "" ? "-" : owner.getProjects()) << "\n";
        cout << "  Teaches:   " << skillList(ownerId, TEACH) << "\n";
        cout << "  Learns:    " << skillList(ownerId, LEARN) << "\n";

        if (canSeeEmail) {
            cout << "  Email:     " << (owner.getEmail() == "" ? "-" : owner.getEmail()) << "\n";
        }
        else {
            cout << "  Email:     (visible to connections only)\n";
        }
    }
    catch (FileException e) {
        cout << "  Error: " << e.message << "\n";
    }
}

// builds a comma-separated list of a user's teach (or learn) skills
string User::skillList(int userId, SkillType type) {
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

// splits "guitar, python " into {"guitar", "python"} skipping empties.
// Keeps spaces inside a skill name ("web development") but trims the edges.
vector<string> User::splitSkills(const string& input) {
    vector<string> result;
    string current = "";
    for (int i = 0; i <= (int)input.length(); i++) {
        if (i == (int)input.length() || input[i] == ',') {
            int start = 0;
            while (start < (int)current.length() && current[start] == ' ') start++;
            int end = (int)current.length();
            while (end > start && current[end - 1] == ' ') end--;
            if (end > start) {
                result.push_back(current.substr(start, end - start));
            }
            current = "";
        }
        else {
            current += input[i];
        }
    }
    return result;
}

} // namespace skillswap