# fun - A modal text editor written in C++
This is the repository for fun - a modal lightweight text editor written in modern C++.

# Dependecies
To build and run this editor you need:
* **A compiler** able to compile C++17 or later
* **ncurses** terminal rendering library

# Installing ncurses
* **Ubuntu/Debian:** `sudo apt-get install libncurses-dev`
* **macOS:** `brew install ncurses`

# Usage
This project uses **CMake** for building.
1. Ensure you have `cmake` and `ncurses` installed.
2. Run the following commands.
```bash
mkdir build
cd build
cmake ..
make
```
3. To run the editor run the following command in the build directory.
```
./fun <file-to-open>
```

> [!WARNING] Currently this project is under development and more features will be added in the future.
