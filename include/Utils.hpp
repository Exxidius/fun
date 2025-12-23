#pragma once

struct Coords {
  int x;
  int y;

  Coords(int x, int y) : x(x), y(y) {}

  inline bool operator!=(const Coords &other) {
    return x != other.x || y != other.y;
  }
  inline void operator+=(const Coords &other) {
    x += other.x;
    y += other.y;
  }
};

enum Mode {
  Standard,
  Typing,
  Quit,
};

enum CursorMode {
  Block = 1,
  Underline = 3,
  Bar = 5,
};
