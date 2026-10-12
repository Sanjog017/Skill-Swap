# Skill-Swap

Our second semester project — a console-based application built in C++ with a
LinkedIn-style flow: build a profile, search people by skill, send connect
requests, and see contact details once connected.

## Build & Run

```bash
cd code/src
g++ -I../include main.cpp menu.cpp account.cpp user.cpp admin.cpp skill.cpp \
    skillrequest.cpp filemanager.cpp validation.cpp login.cpp registration.cpp \
    -o ../bin/skillswap
../bin/skillswap
```

Launch from `code/src/` — the `.txt` data files live there.

## Layout

```
code/include/   all .h files
code/src/       all .cpp files + .txt data files
code/bin/       compiled skillswap   (git-ignored)
```

## Documentation

See `wp.md`, `wof.md`, `Algorithm.md`, `flowchart.md` and `testcase.md`.

## Credits

README written by **anjila26**.
