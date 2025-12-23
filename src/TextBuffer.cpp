#include "../include/TextBuffer.hpp"
#include <fstream>

TextBuffer::TextBuffer(std::string filename) : filename(filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file.");
  }
  std::string line;
  while (std::getline(file, line)) {
    rows.emplace_back(line);
  }

  // TODO: handle empty files
}

std::vector<Row> &TextBuffer::GetRows() { return rows; }

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
    rows.insert(rows.begin() + pos.y + 1, r);
    pos.y++;
    pos.x = 0;
    SetDirty(pos.y, NumRows() - 1);
  } else {
    rows.at(pos.y).InputChar(c, pos.x);
    pos.x++;
  }
}

void TextBuffer::DeleteChar(Coords &pos) {
  if (pos.y >= NumRows()) {
    return;
  }
  pos.x--;
  if (pos.x >= 0) {
    rows.at(pos.y).DeleteChar(pos.x);
  } else {
    if (pos.y == 0) {
      return;
    }
    pos.x = NumCharsAt(pos.y - 1);
    rows.at(pos.y - 1).Append(rows.at(pos.y));
    rows.erase(rows.begin() + pos.y);
    pos.y--;
    SetDirty(pos.y, NumRows() - 1);
  }
}

void TextBuffer::SetDirty(size_t start, size_t end) {
  for (; start <= end; start++) {
    rows.at(start).SetDirty();
  }
}

void TextBuffer::Save() {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file.");
  }
  for (auto &row : rows) {
    row.Write(file);
  }
}
