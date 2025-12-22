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

  void Draw(bool full = false);
  void InputChar(const char c, const Coords pos);
  // TODO: save

private:
  std::vector<Row> rows;
  std::string filename;
};
