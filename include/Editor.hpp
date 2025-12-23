#pragma once
#include "TextBuffer.hpp"
#include <curses.h>
#include <string>
#include <vector>

class Editor {
public:
  Editor(std::string filename);
  ~Editor();

  TextBuffer &ActiveBuffer();

  StandardAction GetStandardAction(const int input);
  TypingAction GetTypingAction(const int input);

  bool CursorChanged();

  void Run();
  void ClampCursor();
  void HandleTyping(const int input);
  void HandleStandard(const int input);
  void ChangeCursor(CursorMode mode);

private:
  void RefreshScreen();

  std::vector<TextBuffer> buffers;
  int active_buffer_idx = -1;
  Coords cursor = Coords(0, 0);
  EditorMode mode = EditorMode::Standard;
  bool running = true;
};
