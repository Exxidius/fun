#include "../include/Row.hpp"
#include <fstream>

Row::Row(std::string line) {
  chars = line;
  if (chars.empty() || chars.back() != '\n') {
    Append("\n");
  }
  if (chars.size() <= 0) {
    throw std::runtime_error("Cannot have lines with zero characters.");
  }
}

size_t Row::NumChars() { return chars.empty() ? 0 : chars.size() - 1; }

std::string &Row::GetRow() { return chars; }

Row Row::Split(const int pos) {
  Row r(chars.substr(pos));
  chars.resize(pos);
  Append("\n");
  if (chars.size() <= 0 && r.chars.size() <= 0) {
    throw std::runtime_error("Cannot have lines with zero characters.");
  }
  is_dirty = true;
  return r;
}

void Row::InputChar(const char c, const int pos) {
  if (pos > chars.size()) {
    throw std::runtime_error("Column index out of range.");
  }
  chars.insert(pos, 1, c);
  is_dirty = true;
}

void Row::SetDirty(bool val) { is_dirty = val; }

bool Row::IsDirty() { return is_dirty; }

void Row::DeleteChar(const int pos) {
  chars.erase(chars.begin() + pos);
  if (chars.size() <= 0) {
    throw std::runtime_error("Cannot have lines with zero characters.");
  }
  is_dirty = true;
}

void Row::Append(const char *s) {
  chars.append(s);
  is_dirty = true;
}

void Row::Append(const Row &other) {
  if (chars.back() == '\n') {
    chars.pop_back();
  }
  chars.append(other.chars);
  is_dirty = true;
}

void Row::Write(std::ofstream &file) { file << chars.c_str(); }
