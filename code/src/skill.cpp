#include "skill.h"

using namespace std;

namespace skillswap {

// initialize static data member to 0
int Skill::count = 0;

// default constructor
Skill::Skill() {
    this->userId = 0;
    this->name = "";
    this->type = TEACH;
    count++;
}

// parameterized constructor — uses this pointer
Skill::Skill(int userId, string name, SkillType type) {
    this->userId = userId;
    this->name = name;
    this->type = type;
    count++;
}

// copy constructor — copies values from another Skill
Skill::Skill(const Skill& other) {
    this->userId = other.userId;
    this->name = other.name;
    this->type = other.type;
    count++;
}

// static member function — returns how many Skill objects exist
int Skill::getCount() {
    return count;
}

// operator overloading — lets us do: cout << skill;
// friend function has access to private members userId, name, type
ostream& operator<<(ostream& out, const Skill& s) {
    string typeName = (s.type == TEACH) ? "Teach" : "Learn";
    out << "[Skill: " << s.name << " (" << typeName << ") by User#" << s.userId << "]";
    return out;
}

} // namespace skillswap
