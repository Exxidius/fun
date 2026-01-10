#pragma once
#include <string>

class Row {
public:
  Row() = default;
  Row(std::string line);

  Row Split(const int pos);

  size_t NumChars();

  bool IsDirty();

  std::string &GetRow();

  void InputChar(const char c, const int pos);
  void Write(std::ofstream &file);
  void SetDirty(bool val = true);
  void DeleteChar(const int pos);
  void Append(const Row &other);
  void Append(const char *s);

private:
  std::string chars;
  bool is_dirty = true;
};
