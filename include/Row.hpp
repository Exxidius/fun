#pragma once
#include <string>

class Row {
public:
  Row() = default;
  Row(std::string line);

  size_t NumChars() { return chars.size(); }

  void Draw(bool full = false);
  void InputChar(const char c, const int x);

private:
  std::string chars;
  bool is_dirty = true;
};
