#pragma once
#include "TextBuffer.hpp"

class Renderer {
public:
  Renderer();
  ~Renderer();

  int GetInput();

  void Draw(TextBuffer &buff, Coords cursor);
};
