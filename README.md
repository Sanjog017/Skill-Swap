# Skill-Swap

A C++ console application where users can trade skills. Currently implemented: Main Menu and Registration.

## Project Structure

```
SkillSwap/
│
├── src/
│   ├── main.cpp
│   ├── menu.h
│   ├── menu.cpp
│   ├── registration.h
│   ├── registration.cpp
│   ├── user.h
│   ├── user.cpp
│   ├── filemanager.h
│   ├── filemanager.cpp
│   ├── validation.h
│   ├── validation.cpp
│   └── users.txt
└── README.md
```

## Build

```
cd src
g++ main.cpp menu.cpp registration.cpp user.cpp filemanager.cpp validation.cpp -o skills
```

## Run

```
cd src
./skills
```

## Data Storage

Users are stored in `users.txt`, one per line, comma separated:

```
Full Name,Username,Password
```
