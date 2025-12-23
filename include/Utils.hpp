#pragma once

#define CTRL_KEY(k) ((k) & 0x1f)
#define KEY_ESC 27
#define KEY_BACKSPACE_ASCII 8
#define KEY_BACKSPACE_DEL 127
#define KEY_ENTER_LINE_FEED 10
#define KEY_ENTER_CARR_RET 13

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
