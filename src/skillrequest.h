#ifndef SKILLREQUEST_H
#define SKILLREQUEST_H

#include "namespace.h"
#include <string>
#include <iostream>

namespace skillswap {

// enumeration for request status
enum RequestStatus {
    PENDING,
    ACCEPTED,
    REJECTED
};

class SkillRequest {
public:
    // default constructor
    SkillRequest();

    // parameterized constructor
    SkillRequest(int id, int fromUser, int toUser, RequestStatus status);

    // copy constructor
    SkillRequest(const SkillRequest& other);

    // getters (inline)
    int getId() const { return id; }
    int getFromUser() const { return fromUser; }
    int getToUser() const { return toUser; }
    RequestStatus getStatus() const { return status; }

    // setter for status
    void setStatus(RequestStatus s) { status = s; }

    // static data member — counts total requests created
    static int count;

    // static member function — returns the current count
    static int getCount();

    // operator overloading — << for printing a SkillRequest
    // friend function — has access to private members
    friend std::ostream& operator<<(std::ostream& out, const SkillRequest& r);

private:
    int id;
    int fromUser;
    int toUser;
    RequestStatus status;
};

} // namespace skillswap

#endif
