#pragma once

constexpr int CTRL_KEY(int k) { return k & 0x1f; }
constexpr int KEY_ESC = 27;
constexpr int KEY_BACKSPACE_ASCII = 8;
constexpr int KEY_BACKSPACE_DEL = 127;
constexpr int KEY_ENTER_LINE_FEED = 10;
constexpr int KEY_ENTER_CARR_RET = 13;

enum class EditorMode {
  Standard,
  Typing,
};

enum class StandardAction {
  MoveUp,
  MoveDown,
  MoveLeft,
  MoveRight,
  Quit,
  Save,
  EnterInsertMode,
  Unknown,
};

enum class TypingAction {
  ExitTypingMode,
  DeletePreviousChar,
  TypeNewline,
  TypeCharacter,
};

enum CursorMode {
  Block = 1,
  Underline = 3,
  Bar = 5,
};

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
