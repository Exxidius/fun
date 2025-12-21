#pragma once
#include "TextBuffer.hpp"
#include <curses.h>
#include <string>
#include <vector>

typedef struct Coords {
  int x;
  int y;

  Coords(int x, int y) : x(x), y(y) {}
} Coords;

class Editor {
public:
  Editor(std::string filename);
  void Run();

private:
  void RefreshScreen();

  std::vector<TextBuffer> buffers;
  int active_buffer = -1;
  Coords cursor = Coords(0, 0);
};
