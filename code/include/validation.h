#ifndef VALIDATION_H
#define VALIDATION_H

#include "namespace.h"
#include <string>

namespace skillswap {

// Validation — static checking functions, called like Validation::isValidName(...)
class Validation {
public:
    static bool isValidName(const std::string& name);        // not empty
    static bool isValidUsername(const std::string& username); // not empty, no spaces
    static bool isValidPassword(const std::string& password); // not empty
    static bool isValidSkill(const std::string& name);        // not empty, no commas
    static bool isValidProgramme(const std::string& programme); // not empty, no commas
    static bool isValidSemester(const std::string& semester); // not empty, no commas
    static bool isValidEmail(const std::string& email);       // has @ and a dot
    static bool isValidProjects(const std::string& projects); // empty ok, else no commas

    static std::string readPassword();   // masked password input ******
};

} // namespace skillswap

#endif