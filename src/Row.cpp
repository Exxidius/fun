#include "../include/Row.hpp"
#include <curses.h>

Row::Row(std::string line) : chars(line) {}

void Row::Draw(bool full) {
  if (!full && !is_dirty) {
    return;
  }
  printw("%s", chars.c_str());
  is_dirty = false;
}

void Row::InputChar(const char c, const int x) {
  if (x > chars.size()) {
    throw new std::runtime_error("Error: Column index out of range.");
  }
  chars.insert(x, 1, c);
  is_dirty = true;
}
