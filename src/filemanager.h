#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "user.h"

class FileManager {
public:
    std::vector<User> loadUsers();
    void saveUser(const User& user);
    bool usernameExists(std::string username);

private:
    std::vector<std::string> splitLine(std::string line, char delimiter);
};

#endif
