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

  std::vector<Row> &GetRows();

  void InputChar(const char c, Coords &pos);
  void DeleteChar(Coords &pos);
  void Save();
  void SetDirty(size_t start, size_t end);

private:
  std::vector<Row> rows;
  std::string filename;
};
