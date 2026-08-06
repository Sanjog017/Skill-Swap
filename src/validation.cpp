// validation.cpp
// IMPLEMENTS the input-checking functions declared in validation.h.
// These functions are small on purpose: one check, one function.

#include "validation.h"
#include <string>

// helper used by the other functions:
// a string is "empty" if it has 0 characters
bool isEmpty(std::string value)
{
    return value.length() == 0;
}

// username rule: it must have at least 1 character AND no spaces.
// spaces are banned because a username with a space is hard to type/read.
bool isValidUsername(std::string username)
{
    if (isEmpty(username))
    {
        return false;                        // 0 characters = bad
    }

    // go through every character one by one
    for (int i = 0; i < username.length(); i++)
    {
        if (username[i] == ' ')              // if we hit a space...
        {
            return false;                    // ...the username is bad
        }
    }

    return true;                             // survived the checks = good
}

bool isValidName(std::string name)
{
    return !isEmpty(name);   // ! means "not" -> true when NOT empty
}

bool isValidPassword(std::string password)
{
    return !isEmpty(password);
}
