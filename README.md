# Skill-Swap

A C++ console application with a **LinkedIn-style flow**, built for an OOP course.

Users build a public profile (programme, semester, projects, teach/learn skills),
search people by skill, send connect requests, and only see each other's
**contact details (email) after they become connections** (a request is accepted).

## Features

- **Register / Login** — masked passwords, validated fields (name, username,
  programme, semester, email, projects). Admin logs in from `admin.txt`.
- **My Profile** — profile card + add/remove teach & learn skills + edit
  programme / semester / email / projects.
- **Search People** — type one or more comma-separated skills; **ANY** match is
  listed, then drill into a full profile and **Send Request** right from there.
- **Requests** — incoming pending requests drill in to the sender's full
  profile, where you **Accept / Reject** them.
- **My Connections** — accepted requests; opening a connection's profile shows
  their private email.
- **Sent Requests** — outgoing requests with status.
- **Admin** — view all users (full profiles), delete a user (cleans up their
  skills and requests), generate a report.

## OOP concepts covered

Classes/access specifiers, constructors (default/parameterized/copy), `this`
pointer, destructor + `new`/`delete`, inheritance (Account → User/Admin),
virtual functions & polymorphism, operator overloading, friend functions &
friend class, static members, inline getters, default arguments, enums,
exception handling, namespaces, and file handling.

## Build & run

```bash
cd src
g++ main.cpp menu.cpp account.cpp user.cpp admin.cpp skill.cpp skillrequest.cpp \
    filemanager.cpp validation.cpp login.cpp registration.cpp -o skillswap
./skillswap
```

Admin login: `admin` / `password` (edit `admin.txt`).

## Data files

| File | Format |
|------|--------|
| users.txt | UserID,Name,Username,Password,Role,Programme,Semester,Projects,Email |
| skills.txt | UserID,SkillName,SkillType (teach/learn) |
| requests.txt | RequestID,FromUser,ToUser,Status (pending/accepted/rejected) |
| admin.txt | admin,password |

An **accepted** request = a **connection**. No field may contain commas
(they are the file separator).