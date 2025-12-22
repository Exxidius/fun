#pragma once
#include "Row.hpp"
#include <vector>

class TextBuffer {
public:
  TextBuffer() = default;
  TextBuffer(std::string filename);

  size_t NumRows() { return rows.size(); }
  size_t NumCharsAt(size_t idx);

  void Draw(bool full = false);

private:
  std::vector<Row> rows;
  std::string filename;
};
