#ifndef NAMESPACE_H
#define NAMESPACE_H

// Everything in this project lives inside this namespace.
// This keeps our classes separate from std and other libraries.
namespace skillswap {

// Forward declarations — tell the compiler these classes exist
// so files can reference each other without full includes.
class Account;
class User;
class Admin;
class Skill;
class SkillRequest;
class FileManager;
class Menu;
class Validation;
class Login;
class Registration;

} // namespace skillswap

#endif
