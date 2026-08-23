#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

class Validation {
public:
    static bool isValidName(std::string name);
    static bool isValidUsername(std::string username);
    static bool isValidPassword(std::string password);
    static bool isValidSkill(std::string name);
    static std::string readPassword();
};

#endif
