#include "filemanager.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string USERS_FILE = "users.txt";
const string SKILLS_FILE = "skills.txt";

// splits "a,b,c" into {"a", "b", "c"}
vector<string> FileManager::splitLine(string line, char delimiter) {
    vector<string> fields;
    string field;
    istringstream stream(line);

    while (getline(stream, field, delimiter)) {
        fields.push_back(field);
    }
    return fields;
}

vector<User> FileManager::loadUsers() {
    vector<User> users;
    ifstream file(USERS_FILE);
    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        vector<string> fields = splitLine(line, ',');
        if (fields.size() >= 5) {
            User u(stoi(fields[0]), fields[1], fields[2], fields[3], fields[4]);
            users.push_back(u);
        }
    }
    file.close();
    return users;
}

void FileManager::saveUser(const User& user) {
    // append mode keeps existing users
    ofstream file(USERS_FILE, ios::app);
    file << user.getId() << "," << user.getName() << ","
         << user.getUsername() << "," << user.getPassword() << ","
         << user.getRole() << endl;
    file.close();
}

bool FileManager::usernameExists(string username) {
    vector<User> users = loadUsers();
    for (User& u : users) {
        if (u.getUsername() == username) {
            return true;
        }
    }
    return false;
}

vector<Skill> FileManager::loadSkills() {
    vector<Skill> skills;
    ifstream file(SKILLS_FILE);
    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        vector<string> fields = splitLine(line, ',');
        if (fields.size() >= 3) {
            Skill s(stoi(fields[0]), fields[1], fields[2]);
            skills.push_back(s);
        }
    }
    file.close();
    return skills;
}

void FileManager::saveSkill(const Skill& skill) {
    // append mode keeps existing skills
    ofstream file(SKILLS_FILE, ios::app);
    file << skill.getUserId() << "," << skill.getName() << ","
         << skill.getType() << endl;
    file.close();
}

bool FileManager::skillExists(int userId, string name, string type) {
    vector<Skill> skills = loadSkills();
    for (Skill& s : skills) {
        if (s.getUserId() == userId && s.getName() == name
            && s.getType() == type) {
            return true;
        }
    }
    return false;
}
