#include "../include/TextBuffer.hpp"
#include <curses.h>
#include <fstream>

TextBuffer::TextBuffer(std::string filename) : filename(filename) {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    line += '\n';
    rows.emplace_back(line);
  }
}

void TextBuffer::Draw(bool full) {
  if (full) {
    clear();
  }

  size_t i = 0;
  for (auto row : rows) {
    move(i, 0);
    row.Draw(full);
    i++;
  }
}

size_t TextBuffer::NumCharsAt(size_t idx) {
  if (idx >= NumRows()) {
    throw new std::runtime_error("Error: Access to buffer out of range.");
  }
  return rows.at(idx).NumChars();
}
