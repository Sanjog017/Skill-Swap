#ifndef MENU_H
#define MENU_H

class Registration;
class Login;
class SkillManager;

class Menu {
public:
    Menu();
    void showMainMenu();
    void clearScreen();

private:
    void pause();
    Registration* registration;
    Login* login;
    SkillManager* skillManager;
};

#endif
