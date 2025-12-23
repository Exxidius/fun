#include "../include/Row.hpp"
#include <curses.h>
#include <fstream>

Row::Row(std::string line) {
  chars = line;
  if (chars.back() != '\n') {
    Append("\n");
  }
  if (chars.size() <= 0) {
    throw std::runtime_error("Cannot have lines with zero characters.");
  }
}

Row Row::Split(const int pos) {
  Row r(chars.substr(pos));
  chars.resize(pos);
  Append("\n");
  if (chars.size() <= 0 && r.chars.size() <= 0) {
    throw std::runtime_error("Cannot have lines with zero characters.");
  }
  return r;
}

size_t Row::NumChars() { return chars.size() > 1 ? chars.size() - 1 : 0; }

void Row::Draw(bool full) {
  if (!full && !is_dirty) {
    return;
  }
  printw("%s", chars.c_str());
  is_dirty = false;
}

void Row::InputChar(const char c, const int pos) {
  if (pos > chars.size()) {
    throw std::runtime_error("Column index out of range.");
  }
  chars.insert(pos, 1, c);
  is_dirty = true;
}

void Row::DeleteChar(const int pos) {
  chars.erase(chars.begin() + pos);
  if (chars.size() <= 0) {
    throw std::runtime_error("Cannot have lines with zero characters.");
  }
}

void Row::Append(const char *s) { chars.append(s); }

void Row::Append(const Row &other) {
  if (chars.back() == '\n') {
    chars.pop_back();
  }
  chars.append(other.chars);
}

void Row::Write(std::ofstream &file) { file << chars.c_str(); }
