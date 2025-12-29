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
  void UpdateScrollOffset(Coords old_cursor);
  void HandleTyping(const int input);
  void HandleStandard(const int input);
  void ChangeCursor(CursorMode mode);

  EditorMode mode = EditorMode::Standard;

  Coords cursor = Coords(0, 0);
  size_t scroll_offset_y = 0;

  // Drawing related
  Renderer renderer = Renderer();

  // Buffer related
  int active_buffer_idx = -1;
  std::vector<TextBuffer> buffers;

  // Operational information
  bool running = true;
};
