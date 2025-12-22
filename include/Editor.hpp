#pragma once
#include "TextBuffer.hpp"
#include <curses.h>
#include <string>
#include <vector>

typedef struct Coords {
  int x;
  int y;

  Coords(int x, int y) : x(x), y(y) {}

  inline bool operator!=(const Coords &other) {
    return x != other.x || y != other.y;
  }
} Coords;

class Editor {
public:
  Editor(std::string filename);
  ~Editor();

  TextBuffer &ActiveBuffer();

  bool CursorChanged();

  void Run();
  void ClampCursor();

private:
  void RefreshScreen();

  std::vector<TextBuffer> buffers;
  int active_buffer_idx = -1;
  Coords cursor = Coords(0, 0);
};
