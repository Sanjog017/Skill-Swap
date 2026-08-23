#ifndef SKILL_H
#define SKILL_H

#include <string>

class Menu;
class Login;

// one skill in skills.txt: UserID,SkillName,SkillType
class Skill {
public:
    Skill(int userId, std::string name, std::string type);

    int getUserId() const;
    std::string getName() const;
    std::string getType() const;

private:
    int userId;
    std::string name;
    std::string type;       // "teach" or "learn"
};

// the menu a normal user sees after logging in
class SkillManager {
public:
    SkillManager(Menu* menu);
    void showUserMenu(Login* login);

private:
    void addSkill(Login* login, std::string type);
    void viewMySkills(Login* login);

    Menu* menu;
};

#endif
