#include "skill.h"
#include "menu.h"
#include "login.h"
#include "filemanager.h"
#include "validation.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Skill::Skill(int userId, string name, string type) {
    this->userId = userId;
    this->name = name;
    this->type = type;
}

int Skill::getUserId() const {
    return userId;
}

string Skill::getName() const {
    return name;
}

string Skill::getType() const {
    return type;
}

SkillManager::SkillManager(Menu* menu) {
    this->menu = menu;
}

void SkillManager::showUserMenu(Login* login) {
    string choice;

    while (true) {
        menu->clearScreen();

        cout << "=== User Menu (@"
             << login->getCurrentUsername() << ") ===" << endl;
        cout << "1. Add Teach Skill" << endl;
        cout << "2. Add Learn Skill" << endl;
        cout << "3. View My Skills" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter choice: ";

        // exit if there is no more input (Ctrl+D / end of file)
        if (!getline(cin, choice)) {
            return;
        }

        if (choice == "1") {
            addSkill(login, "teach");
        }
        else if (choice == "2") {
            addSkill(login, "learn");
        }
        else if (choice == "3") {
            viewMySkills(login);
        }
        else if (choice == "4") {
            cout << "Logged out!" << endl;
            return;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }

        cout << "Press Enter to continue...";
        string dummy;
        getline(cin, dummy);

        // stop if input ended while pausing
        if (!cin) {
            return;
        }
    }
}

void SkillManager::addSkill(Login* login, string type) {
    FileManager fileManager;

    if (type == "teach") {
        cout << "=== Add Teach Skill ===" << endl;
    }
    else {
        cout << "=== Add Learn Skill ===" << endl;
    }

    cout << "Enter skill name: ";
    string name;
    getline(cin, name);

    // cancel if input ends (Ctrl+D / end of file)
    if (cin.eof()) {
        return;
    }

    if (!Validation::isValidSkill(name)) {
        cout << "Skill name cannot be empty or contain commas." << endl;
        return;
    }

    int userId = login->getCurrentUserId();

    if (fileManager.skillExists(userId, name, type)) {
        cout << "You already added that skill." << endl;
        return;
    }

    Skill skill(userId, name, type);
    fileManager.saveSkill(skill);

    cout << "Skill added!" << endl;
}

void SkillManager::viewMySkills(Login* login) {
    FileManager fileManager;
    vector<Skill> skills = fileManager.loadSkills();
    int userId = login->getCurrentUserId();

    cout << "=== My Skills ===" << endl;

    // show teach skills first
    cout << "Teach:" << endl;
    bool anyTeach = false;
    for (Skill& s : skills) {
        if (s.getUserId() == userId && s.getType() == "teach") {
            cout << " - " << s.getName() << endl;
            anyTeach = true;
        }
    }
    if (!anyTeach) {
        cout << " (none)" << endl;
    }

    // then learn skills
    cout << "Learn:" << endl;
    bool anyLearn = false;
    for (Skill& s : skills) {
        if (s.getUserId() == userId && s.getType() == "learn") {
            cout << " - " << s.getName() << endl;
            anyLearn = true;
        }
    }
    if (!anyLearn) {
        cout << " (none)" << endl;
    }
}
