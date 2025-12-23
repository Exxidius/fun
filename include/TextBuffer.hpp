#pragma once
#include "Row.hpp"
#include "Utils.hpp"
#include <vector>

class TextBuffer {
public:
  TextBuffer() = default;
  TextBuffer(std::string filename);

  size_t NumRows() { return rows.size(); }
  size_t NumCharsAt(size_t idx);

  void InputChar(const char c, Coords &pos);
  void DeleteChar(Coords &pos);
  void Draw(bool full = false);
  void Save();

private:
  std::vector<Row> rows;
  std::string filename;
};
