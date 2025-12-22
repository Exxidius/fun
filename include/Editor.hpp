#pragma once
#include "TextBuffer.hpp"
#include <curses.h>
#include <string>
#include <vector>

#define KEY_ESC 27

class Editor {
public:
  Editor(std::string filename);
  ~Editor();

  TextBuffer &ActiveBuffer();

  bool CursorChanged();

  void Run();
  void ClampCursor();
  void HandleTyping(const char c);
  void HandleStandard(const char c);
  void ChangeCursor(CursorMode mode);

private:
  void RefreshScreen();

  std::vector<TextBuffer> buffers;
  int active_buffer_idx = -1;
  Coords cursor = Coords(0, 0);
  Mode mode = Mode::Standard;
};
