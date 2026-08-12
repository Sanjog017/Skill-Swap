#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "filemanager.h"

class Menu;

class Registration {
public:
    Registration(Menu* menu);
    void registerUser();

private:
    Menu* menu;
    FileManager fileManager;
};

#endif
