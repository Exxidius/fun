#include "../include/Editor.hpp"
#include <algorithm>

Editor::Editor(std::string filename) {
  buffers.emplace_back(filename);
  active_buffer_idx = 0;

  initscr();
  cbreak();
  noecho();
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
    char action = getch();
    if (action == 'q') {
      return;
    }
    switch (action) {
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
    }
    ClampCursor();
    RefreshScreen();
  }
}

Editor::~Editor() { endwin(); }
