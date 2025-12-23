#include "../include/Row.hpp"
#include <curses.h>
#include <fstream>

Row::Row(std::string line) : chars(line) {}

Row Row::Split(const int pos) {
  Row r(chars.substr(pos));
  chars.resize(pos);
  return r;
}

void Row::Draw(bool full) {
  if (!full && !is_dirty) {
    return;
  }
  printw("%s", chars.c_str());
  is_dirty = false;
}

void Row::InputChar(const char c, const int pos) {
  if (pos > chars.size()) {
    throw new std::runtime_error("Error: Column index out of range.");
  }
  chars.insert(pos, 1, c);
  is_dirty = true;
}

void Row::DeleteChar(const int pos) { chars.erase(chars.begin() + pos); }

void Row::Append(const Row &other) {
  chars.pop_back();
  chars.append(other.chars);
}

void Row::Write(std::ofstream &file) { file << chars.c_str(); }
