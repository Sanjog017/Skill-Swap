#ifndef USER_H
#define USER_H

#include "account.h"
#include "skill.h"
#include <vector>

namespace skillswap {

// User inherits from Account — a regular user with a profile
// (semester, projects, email) plus teach/learn skills.
class User : public Account {
public:
    // default constructor — an empty user
    User();

    // parameterized constructor — passes everything up to Account
    User(int id, std::string name, std::string username,
         std::string password, std::string role = "user",
         std::string programme = "", std::string semester = "",
         std::string projects = "", std::string email = "");

    // copy constructor
    User(const User& other);

    // getters (inline)
    std::string getProgramme() const { return programme; }
    std::string getSemester() const { return semester; }
    std::string getProjects() const { return projects; }
    std::string getEmail() const { return email; }

    // setters — used when editing the profile
    void setProgramme(std::string p) { programme = p; }
    void setSemester(std::string s) { semester = s; }
    void setProjects(std::string p) { projects = p; }
    void setEmail(std::string e) { email = e; }

    // static data member — the next free user id
    static int nextId;

    // static member function — returns the next free id
    static int getNextId();

    // operator overloading — << for printing a User
    // friend function — has access to private members
    friend std::ostream& operator<<(std::ostream& out, const User& u);

    // friend class — FileManager can read/write our private members
    friend class FileManager;

    // overrides Account's pure virtual function
    void displayMenu() override;

private:
    std::string programme;   // course being studied (public on the profile card)
    std::string semester;    // profile info (public on the profile card)
    std::string projects;
    std::string email;       // contact — only shown to connections

    // terminal helpers
    void clearScreen();            // clears the terminal
    void pause();                  // waits for Enter key
    void printBoxLine(std::string text, int width);   // prints one box line

    // menu screens
    void viewMyProfile();          // own profile + edit options
    void addSkill(SkillType type); // add a teach or learn skill
    void removeSkill();            // remove one of my skills
    void editProfile();            // change semester / projects / email
    void searchPeople();           // search users by skill, open profiles
    void openProfile(int ownerId); // full profile + send request
    void sendRequest(int toId);    // sends a pending request
    void viewRequests();           // incoming pending requests, drill-in
    void viewConnections();        // accepted connections, profiles open
    void viewSentRequests();       // outgoing requests with status

    // helper for showing one profile (handles the privacy rule):
    void showProfile(int ownerId);

    // builds "guitar, python" from a user's teach (or learn) skills
    std::string skillList(int userId, SkillType type);

    // splits "guitar, python " into {"guitar", "python"} skipping empties
    std::vector<std::string> splitSkills(const std::string& input);
};

} // namespace skillswap

#endif