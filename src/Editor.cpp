#include "../include/Editor.hpp"
#include <algorithm>
#include <iostream>

Editor::Editor(std::string filename) {
  buffers.emplace_back(filename);
  active_buffer_idx = 0;

  initscr();
  cbreak();
  noecho();
  raw();
  nodelay(stdscr, TRUE);
}

bool Editor::CursorChanged() {
  int x, y;
  getyx(stdscr, y, x);
  return Coords(x, y) != cursor;
}

void Editor::RefreshScreen() {
  ActiveBuffer().Draw(CursorChanged());
  move(cursor.y, cursor.x);
  refresh();
}

TextBuffer &Editor::ActiveBuffer() {
  if (active_buffer_idx < 0) {
    throw new std::runtime_error("Error: No Buffer active!");
  }
  return buffers.at(active_buffer_idx);
}

void Editor::ClampCursor() {
  cursor.y = std::clamp(cursor.y, 0, (int)ActiveBuffer().NumRows() - 1);
  cursor.x =
      std::clamp(cursor.x, 0, (int)ActiveBuffer().NumCharsAt(cursor.y) - 1);
}

void Editor::Run() {
  clear();
  while (true) {
    char c = getch();
    switch (mode) {
    case Mode::Typing:
      HandleTyping(c);
      break;
    case Mode::Standard:
      HandleStandard(c);
      break;
    case Mode::Quit:
      return;
    }
    ClampCursor();
    RefreshScreen();
  }
}

void Editor::HandleStandard(const char c) {
  switch (c) {
  case 'q':
    mode = Mode::Quit;
    break;
  case CTRL_KEY('s'):
    ActiveBuffer().Save();
    break;
  case 'h':
    cursor.x--;
    break;
  case 'j':
    cursor.y++;
    break;
  case 'k':
    cursor.y--;
    break;
  case 'l':
    cursor.x++;
    break;
  case 'i':
    ChangeCursor(CursorMode::Bar);
    mode = Mode::Typing;
    break;
  }
}

void Editor::HandleTyping(const char c) {
  switch (c) {
  case ERR: // Nothing to do here
    break;
  case KEY_ESC:
    ChangeCursor(CursorMode::Block);
    mode = Mode::Standard;
    break;
  case KEY_BACKSPACE:
  case KEY_BACKSPACE_ASCII:
  case KEY_BACKSPACE_DEL:
    ActiveBuffer().DeleteChar(cursor);
    break;
  case KEY_ENTER_CARR_RET:
  case KEY_ENTER_LINE_FEED:
  case KEY_ENTER:
    ActiveBuffer().InputChar('\n', cursor);
    break;
  default:
    ActiveBuffer().InputChar(c, cursor);
    break;
  }
}

void Editor::ChangeCursor(CursorMode shape) {
  std::cout << "\033[" << shape << " q" << std::flush;
}

Editor::~Editor() { endwin(); }
