#include "../include/TextBuffer.hpp"
#include <curses.h>
#include <fstream>

TextBuffer::TextBuffer(std::string filename) : filename(filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw new std::runtime_error("Error: could not open file.");
  }
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
    return 0;
  }
  return rows.at(idx).NumChars();
}

void TextBuffer::InputChar(const char c, Coords &pos) {
  if (c == '\n') {
    if (pos.y >= NumRows() || pos.y < 0) {
      return;
    }
    Row r = rows.at(pos.y).Split(pos.x);
    rows.at(pos.y).InputChar('\n', pos.x);
    rows.insert(rows.begin() + pos.y + 1, r);
    pos.y++;
    pos.x = 0;
  } else {
    rows.at(pos.y).InputChar(c, pos.x);
    pos.x++;
  }
}

void TextBuffer::DeleteChar(Coords &pos) {
  if (pos.y >= NumRows() || pos.y <= 0) {
    return;
  }
  pos.x--;
  if (pos.x >= 0) {
    rows.at(pos.y).DeleteChar(pos.x);
  } else {
    rows.at(pos.y - 1).Append(rows.at(pos.y));
    rows.erase(rows.begin() + pos.y);
    pos.y--;
    pos.x = NumCharsAt(pos.y);
  }
}

void TextBuffer::Save() {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw new std::runtime_error("Error: could not open file.");
  }
  for (auto row : rows) {
    row.Write(file);
  }
}
