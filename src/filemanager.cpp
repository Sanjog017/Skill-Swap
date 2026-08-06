// filemanager.cpp
// IMPLEMENTS the file functions declared in filemanager.h.
//
// HOW users.txt IS FORMATTED:
//   one user per line, fields separated by commas
//   John Doe,john,pass123
//   (full name, username, password)

#include "filemanager.h"
#include <fstream>    // for reading/writing files (ifstream / ofstream)
#include <iostream>
#include <string>

// the name of the file where all users are stored
const std::string USERS_FILE = "users.txt";

// splits one line like "John,john,pass" into separate parts.
// fields[0] = John, fields[1] = john, fields[2] = pass
// It walks the line character by character and cuts the line
// wherever it finds a comma.
void splitLine(std::string line, std::string fields[], int size)
{
    std::string part = "";   // builds up one field at a time
    int index = 0;           // which field we are filling right now

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ',')              // found a comma -> field is done
        {
            fields[index] = part;        // save the finished field
            part = "";                   // start the next field fresh
            index++;                     // move to the next slot
        }
        else
        {
            part = part + line[i];       // keep adding characters to the field
        }
    }
    fields[index] = part;                // save the last field (no comma after it)
}

// reads users.txt line by line and compares each username (field 1)
// with the one we are checking. true = username is taken.
bool usernameExists(std::string username)
{
    std::ifstream file(USERS_FILE);   // open file for READING
    std::string line;

    // if the file does not exist yet, no one has that username
    if (!file.is_open())
    {
        return false;
    }

    // getline reads one full line of the file each time the loop runs
    while (getline(file, line))
    {
        std::string fields[3];          // a line has 3 parts: name, username, password
        splitLine(line, fields, 3);

        if (fields[1] == username)      // fields[1] = the username column
        {
            file.close();               // done with the file
            return true;                // found a match
        }
    }

    file.close();
    return false;                       // loop ended, never matched
}

// appends (adds at the end) one user to users.txt.
// std::ios::app means "append": never delete what is already there.
void saveUser(const User& user)
{
    std::ofstream file(USERS_FILE, std::ios::app);   // open file for WRITING (append mode)

    if (!file.is_open())
    {
        std::cout << "Could not open " << USERS_FILE << ".\n";
        return;
    }

    // write the user as one line: name,username,password then a newline
    file << user.getName() << "," << user.getUsername() << "," << user.getPassword() << "\n";
    file.close();   // always close the file when done
}
