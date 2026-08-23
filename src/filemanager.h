#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "user.h"
#include "skill.h"

class FileManager {
public:
    std::vector<User> loadUsers();
    void saveUser(const User& user);
    bool usernameExists(std::string username);

    std::vector<Skill> loadSkills();
    void saveSkill(const Skill& skill);
    bool skillExists(int userId, std::string name, std::string type);

private:
    std::vector<std::string> splitLine(std::string line, char delimiter);
};

#endif
