#pragma once
#include "Renderer.hpp"
#include "TextBuffer.hpp"
#include <string>
#include <vector>

class Editor {
public:
  Editor(std::string filename);

  void Run();

private:
  TextBuffer &ActiveBuffer();

  StandardAction GetStandardAction(const int input);
  TypingAction GetTypingAction(const int input);

  void ClampCursor();
  void HandleTyping(const int input);
  void HandleStandard(const int input);
  void ChangeCursor(CursorMode mode);

  std::vector<TextBuffer> buffers;
  int active_buffer_idx = -1;
  Coords cursor = Coords(0, 0);
  EditorMode mode = EditorMode::Standard;
  bool running = true;
  Renderer renderer = Renderer();
};
