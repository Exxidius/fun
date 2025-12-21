#pragma once
#include "Row.hpp"
#include <vector>

class TextBuffer {
public:
  TextBuffer() = default;
  TextBuffer(std::string filename);

  std::vector<Row> GetLines() { return rows; }

private:
  std::vector<Row> rows;
  std::string filename;
};
