#include "skillrequest.h"

using namespace std;

namespace skillswap {

// initialize static data member to 0
int SkillRequest::count = 0;

// default constructor
SkillRequest::SkillRequest() {
    this->id = 0;
    this->fromUser = 0;
    this->toUser = 0;
    this->status = PENDING;
    count++;
}

// parameterized constructor — uses this pointer
SkillRequest::SkillRequest(int id, int fromUser, int toUser, RequestStatus status) {
    this->id = id;
    this->fromUser = fromUser;
    this->toUser = toUser;
    this->status = status;
    count++;
}

// copy constructor — copies values from another SkillRequest
SkillRequest::SkillRequest(const SkillRequest& other) {
    this->id = other.id;
    this->fromUser = other.fromUser;
    this->toUser = other.toUser;
    this->status = other.status;
    count++;
}

// static member function — returns how many SkillRequest objects exist
int SkillRequest::getCount() {
    return count;
}

// operator overloading — lets us do: cout << request;
// friend function has access to private members
ostream& operator<<(ostream& out, const SkillRequest& r) {
    string statusName;
    if (r.status == PENDING)   statusName = "Pending";
    else if (r.status == ACCEPTED) statusName = "Accepted";
    else statusName = "Rejected";

    out << "[Request#" << r.id << ": User#" << r.fromUser
        << " -> User#" << r.toUser << " (" << statusName << ")]";
    return out;
}

} // namespace skillswap
