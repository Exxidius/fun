#pragma once
#include "TextBuffer.hpp"

struct ScreenSize {
  int rows;
  int cols;
};

constexpr int view_offset_y = 1;

class Renderer {
public:
  Renderer();
  ~Renderer();

  ScreenSize GetScreenSize() const;

  int GetInput();

  void Draw(TextBuffer &buff, Coords cursor, size_t scroll_offset_y);
};
