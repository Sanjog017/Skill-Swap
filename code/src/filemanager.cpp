#include "filemanager.h"
#include <fstream>
#include <sstream>

using namespace std;

namespace skillswap {

// splits "a,b,c" into {"a","b","c"}
vector<string> FileManager::splitLine(const string& line, char delimiter) {
    vector<string> parts;
    string current = "";
    for (int i = 0; i < (int)line.length(); i++) {
        if (line[i] == delimiter) {
            parts.push_back(current);
            current = "";
        }
        else {
            current += line[i];
        }
    }
    parts.push_back(current);   // the last piece
    return parts;
}

// reads every user from users.txt
vector<User> FileManager::loadUsers() {
    vector<User> users;
    ifstream in("users.txt");
    if (!in) {
        return users;   // no file yet = no users
    }
    string line;
    while (getline(in, line)) {
        if (line == "") continue;
        vector<string> parts = splitLine(line, ',');
        if (parts.size() < 9) continue;   // ignore broken lines
        int userId = -1;
        try {
            userId = stoi(parts[0]);      // String To Int
        }
        catch (...) {
            continue;
        }
        // we are a friend of User, so we can fill the private members directly
        User u;
        u.id = userId;
        u.name = parts[1];
        u.username = parts[2];
        u.password = parts[3];
        u.role = parts[4];
        u.programme = parts[5];
        u.semester = parts[6];
        u.projects = parts[7];
        u.email = parts[8];
        users.push_back(u);
    }
    if (users.size() > 0) {
        User::nextId = users[users.size() - 1].getId() + 1;   // refresh the static
    }
    return users;
}

// adds one new user to users.txt
void FileManager::saveUser(const User& u) {
    ofstream out("users.txt", ios::app);
    if (!out) {
        throw FileException("could not open users.txt for writing");
    }
    out << u.id << "," << u.name << "," << u.username << ","
        << u.password << "," << u.role << "," << u.programme << ","
        << u.semester << "," << u.projects << "," << u.email << "\n";
}

// returns true if a username is already used (blocked by registration)
bool FileManager::usernameExists(const string& username) {
    vector<User> users = loadUsers();
    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i].username == username) {
            return true;
        }
    }
    return false;
}

// the next free user id = biggest id + 1
int FileManager::nextUserId() {
    vector<User> users = loadUsers();
    if (users.size() == 0) {
        return 1;
    }
    return users[users.size() - 1].getId() + 1;
}

// finds a user id from a username (-1 if not found)
int FileManager::findUserIdByUsername(const string& username) {
    vector<User> users = loadUsers();
    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i].username == username) {
            return users[i].id;
        }
    }
    return -1;
}

// returns the user with this id (or an empty user with id -1 if not found)
User FileManager::getUserById(int userId) {
    vector<User> users = loadUsers();
    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i].id == userId) {
            return users[i];
        }
    }
    return User();
}

// updates the profile fields of one user, then rewrites the file
void FileManager::updateUserProfile(int userId, const string& programme,
                                    const string& semester,
                                    const string& projects, const string& email) {
    vector<User> users = loadUsers();
    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i].id == userId) {
            users[i].programme = programme;
            users[i].semester = semester;
            users[i].projects = projects;
            users[i].email = email;
            break;
        }
    }
    writeAllUsers(users);
}

// removes a user and everything connected to them
void FileManager::deleteUser(int userId) {
    vector<User> users = loadUsers();
    vector<User> remainingUsers;
    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i].id != userId) {
            remainingUsers.push_back(users[i]);
        }
    }
    writeAllUsers(remainingUsers);

    vector<Skill> skills = loadSkills();
    vector<Skill> remainingSkills;
    for (int i = 0; i < (int)skills.size(); i++) {
        if (skills[i].userId != userId) {
            remainingSkills.push_back(skills[i]);
        }
    }
    writeAllSkills(remainingSkills);

    vector<SkillRequest> requests = loadRequests();
    vector<SkillRequest> remainingRequests;
    for (int i = 0; i < (int)requests.size(); i++) {
        if (requests[i].fromUser != userId && requests[i].toUser != userId) {
            remainingRequests.push_back(requests[i]);
        }
    }
    writeAllRequests(remainingRequests);
}

// rewrites the whole users.txt file
void FileManager::writeAllUsers(const vector<User>& users) {
    ofstream out("users.txt");
    if (!out) {
        throw FileException("could not open users.txt for writing");
    }
    for (int i = 0; i < (int)users.size(); i++) {
        const User& u = users[i];
        out << u.id << "," << u.name << "," << u.username << ","
            << u.password << "," << u.role << "," << u.programme << ","
            << u.semester << "," << u.projects << "," << u.email << "\n";
    }
}

// reads every skill from skills.txt
vector<Skill> FileManager::loadSkills() {
    vector<Skill> skills;
    ifstream in("skills.txt");
    if (!in) {
        return skills;
    }
    string line;
    while (getline(in, line)) {
        if (line == "") continue;
        vector<string> parts = splitLine(line, ',');
        if (parts.size() < 3) continue;
        int userId = -1;
        try {
            userId = stoi(parts[0]);
        }
        catch (...) {
            continue;
        }
        // friend access to private members
        Skill s;
        s.userId = userId;
        s.name = parts[1];
        s.type = (parts[2] == "teach") ? TEACH : LEARN;
        skills.push_back(s);
    }
    return skills;
}

// adds one new skill to skills.txt
void FileManager::saveSkill(const Skill& s) {
    ofstream out("skills.txt", ios::app);
    if (!out) {
        throw FileException("could not open skills.txt for writing");
    }
    const char* typeName = (s.type == TEACH) ? "teach" : "learn";
    out << s.userId << "," << s.name << "," << typeName << "\n";
}

// returns true if this user already has a skill with this name
bool FileManager::skillExists(int userId, const string& name) {
    vector<Skill> skills = loadSkills();
    for (int i = 0; i < (int)skills.size(); i++) {
        if (skills[i].userId == userId && skills[i].name == name) {
            return true;
        }
    }
    return false;
}

// every skill that belongs to one user
vector<Skill> FileManager::skillsOf(int userId) {
    vector<Skill> skills = loadSkills();
    vector<Skill> mine;
    for (int i = 0; i < (int)skills.size(); i++) {
        if (skills[i].userId == userId) {
            mine.push_back(skills[i]);
        }
    }
    return mine;
}

// removes one skill from skills.txt
void FileManager::removeSkill(int userId, const string& name) {
    vector<Skill> skills = loadSkills();
    vector<Skill> remaining;
    for (int i = 0; i < (int)skills.size(); i++) {
        if (!(skills[i].userId == userId && skills[i].name == name)) {
            remaining.push_back(skills[i]);
        }
    }
    writeAllSkills(remaining);
}

// rewrites the whole skills.txt file
void FileManager::writeAllSkills(const vector<Skill>& skills) {
    ofstream out("skills.txt");
    if (!out) {
        throw FileException("could not open skills.txt for writing");
    }
    for (int i = 0; i < (int)skills.size(); i++) {
        const Skill& s = skills[i];
        const char* typeName = (s.type == TEACH) ? "teach" : "learn";
        out << s.userId << "," << s.name << "," << typeName << "\n";
    }
}

// reads every request from requests.txt
vector<SkillRequest> FileManager::loadRequests() {
    vector<SkillRequest> requests;
    ifstream in("requests.txt");
    if (!in) {
        return requests;
    }
    string line;
    while (getline(in, line)) {
        if (line == "") continue;
        vector<string> parts = splitLine(line, ',');
        if (parts.size() < 4) continue;
        int id = -1;
        int fromUser = -1;
        int toUser = -1;
        try {
            id = stoi(parts[0]);
            fromUser = stoi(parts[1]);
            toUser = stoi(parts[2]);
        }
        catch (...) {
            continue;
        }
        RequestStatus status = PENDING;
        if (parts[3] == "accepted") status = ACCEPTED;
        else if (parts[3] == "rejected") status = REJECTED;
        // friend access to private members
        SkillRequest r;
        r.id = id;
        r.fromUser = fromUser;
        r.toUser = toUser;
        r.status = status;
        requests.push_back(r);
    }
    return requests;
}

// adds one new request to requests.txt
void FileManager::saveRequest(const SkillRequest& r) {
    ofstream out("requests.txt", ios::app);
    if (!out) {
        throw FileException("could not open requests.txt for writing");
    }
    const char* statusName = (r.status == PENDING) ? "pending"
                           : (r.status == ACCEPTED) ? "accepted" : "rejected";
    out << r.id << "," << r.fromUser << "," << r.toUser << "," << statusName << "\n";
}

// the next free request id = biggest id + 1
int FileManager::nextRequestId() {
    vector<SkillRequest> requests = loadRequests();
    if (requests.size() == 0) {
        return 1;
    }
    return requests[requests.size() - 1].getId() + 1;
}

// returns true if there is still a pending request fromUser -> toUser
bool FileManager::pendingExists(int fromUser, int toUser) {
    vector<SkillRequest> requests = loadRequests();
    for (int i = 0; i < (int)requests.size(); i++) {
        if (requests[i].fromUser == fromUser && requests[i].toUser == toUser
            && requests[i].status == PENDING) {
            return true;
        }
    }
    return false;
}

// returns true if two users already accepted a request (they are connected)
bool FileManager::areConnected(int a, int b) {
    vector<SkillRequest> requests = loadRequests();
    for (int i = 0; i < (int)requests.size(); i++) {
        if (requests[i].status == ACCEPTED) {
            bool fromA = (requests[i].fromUser == a && requests[i].toUser == b);
            bool fromB = (requests[i].fromUser == b && requests[i].toUser == a);
            if (fromA || fromB) {
                return true;
            }
        }
    }
    return false;
}

// changes the status of a request, then rewrites the file
void FileManager::updateRequestStatus(int id, RequestStatus status) {
    vector<SkillRequest> requests = loadRequests();
    for (int i = 0; i < (int)requests.size(); i++) {
        if (requests[i].id == id) {
            requests[i].status = status;   // friend access to private member
            break;
        }
    }
    writeAllRequests(requests);
}

// rewrites the whole requests.txt file
void FileManager::writeAllRequests(const vector<SkillRequest>& requests) {
    ofstream out("requests.txt");
    if (!out) {
        throw FileException("could not open requests.txt for writing");
    }
    for (int i = 0; i < (int)requests.size(); i++) {
        const SkillRequest& r = requests[i];
        const char* statusName = (r.status == PENDING) ? "pending"
                               : (r.status == ACCEPTED) ? "accepted" : "rejected";
        out << r.id << "," << r.fromUser << "," << r.toUser << "," << statusName << "\n";
    }
}

// checks the admin credentials in admin.txt
bool FileManager::adminExists(const string& username, const string& password) {
    ifstream in("admin.txt");
    if (!in) {
        return false;
    }
    string line;
    if (!getline(in, line)) {
        return false;
    }
    vector<string> parts = splitLine(line, ',');
    if (parts.size() < 2) {
        return false;
    }
    return parts[0] == username && parts[1] == password;
}

} // namespace skillswap