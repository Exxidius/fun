#pragma once
#include <string>

class Row {
public:
  Row() = default;
  Row(std::string line);

  std::string GetChars() { return chars; }

private:
  std::string chars;
};
