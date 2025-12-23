#pragma once
#include "TextBuffer.hpp"
#include <curses.h>
#include <string>
#include <vector>

#define CTRL_KEY(k) ((k) & 0x1f)
#define KEY_ESC 27
#define KEY_BACKSPACE_ASCII 8
#define KEY_BACKSPACE_DEL 127
#define KEY_ENTER_LINE_FEED 10
#define KEY_ENTER_CARR_RET 13

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
