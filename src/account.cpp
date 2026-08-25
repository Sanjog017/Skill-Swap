#include "account.h"

using namespace std;

namespace skillswap {

// constructor — uses this pointer to set each member
Account::Account(int id, string name, string username,
                 string password, string role) {
    this->id = id;
    this->name = name;
    this->username = username;
    this->password = password;
    this->role = role;
}

// virtual destructor — derived class destructors will also run
Account::~Account() {
}

} // namespace skillswap
