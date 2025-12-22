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
