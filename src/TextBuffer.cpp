#include "../include/TextBuffer.hpp"
#include <fstream>

TextBuffer::TextBuffer(std::string filename) : filename(filename) {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    line += '\n';
    rows.emplace_back(line);
  }
}
