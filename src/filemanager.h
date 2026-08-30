#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "user.h"
#include "skill.h"
#include "skillrequest.h"
#include <vector>
#include <string>

namespace skillswap {

// custom exception — thrown when a data file cannot be written
class FileException {
public:
    FileException(std::string msg) : message(msg) {}
    std::string message;
};

// FileManager — the only class that touches the .txt files.
// It is a friend class of User, Skill and SkillRequest so it can
// read/write their private members directly.
class FileManager {
public:
    // --- users (users.txt: id,name,username,password,role,programme,semester,projects,email) ---
    std::vector<User> loadUsers();
    void saveUser(const User& u);
    bool usernameExists(const std::string& username);
    int nextUserId();                              // biggest id + 1
    int findUserIdByUsername(const std::string& username);
    User getUserById(int userId);
    void updateUserProfile(int userId, const std::string& programme,
                           const std::string& semester,
                           const std::string& projects, const std::string& email);
    void deleteUser(int userId);                   // removes user + skills + requests

    // --- skills (skills.txt: id,name,type) ---
    std::vector<Skill> loadSkills();
    void saveSkill(const Skill& s);
    bool skillExists(int userId, const std::string& name);
    std::vector<Skill> skillsOf(int userId);
    void removeSkill(int userId, const std::string& name);

    // --- requests (requests.txt: id,from,to,status) ---
    std::vector<SkillRequest> loadRequests();
    void saveRequest(const SkillRequest& r);
    int nextRequestId();                           // biggest id + 1
    bool pendingExists(int fromUser, int toUser);  // pending request from -> to
    bool areConnected(int a, int b);               // accepted request between them
    void updateRequestStatus(int id, RequestStatus status);

    // --- admin (admin.txt: admin,password) ---
    bool adminExists(const std::string& username, const std::string& password);

private:
    std::vector<std::string> splitLine(const std::string& line, char delimiter);
    void writeAllUsers(const std::vector<User>& users);
    void writeAllSkills(const std::vector<Skill>& skills);
    void writeAllRequests(const std::vector<SkillRequest>& requests);
};

} // namespace skillswap

#endif