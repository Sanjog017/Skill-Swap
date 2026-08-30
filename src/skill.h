#ifndef SKILL_H
#define SKILL_H

#include "namespace.h"
#include <string>
#include <iostream>

namespace skillswap {

// enumeration for skill type — teaches or wants to learn
enum SkillType {
    TEACH,
    LEARN
};

class Skill {
public:
    // default constructor
    Skill();

    // parameterized constructor
    Skill(int userId, std::string name, SkillType type);

    // copy constructor
    Skill(const Skill& other);

    // getters (inline)
    int getUserId() const { return userId; }
    std::string getName() const { return name; }
    SkillType getType() const { return type; }

    // static data member — counts total skills created
    static int count;

    // static member function — returns the current count
    static int getCount();

    // operator overloading — << for printing a Skill
    // friend function — has access to private members
    friend std::ostream& operator<<(std::ostream& out, const Skill& s);

    // friend class — FileManager can read/write our private members
    friend class FileManager;

private:
    int userId;
    std::string name;
    SkillType type;
};

} // namespace skillswap

#endif
