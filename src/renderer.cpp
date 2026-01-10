#include "../include/Renderer.hpp"
#include <curses.h>

Renderer::Renderer() {
  initscr();
  cbreak();
  noecho();
  raw();
}

ScreenSize Renderer::GetScreenSize() const {
  int x, y;
  getmaxyx(stdscr, y, x);
  return {y - view_offset_y, x};
}

int Renderer::GetInput() { return getch(); }

void Renderer::Draw(TextBuffer &buf, Coords cursor, size_t scroll_offset_y) {
  ScreenSize win = GetScreenSize();
  for (size_t i = 0; i < win.rows; i++) {
    move(i, 0);
    clrtoeol();
    move(i, 0);

    size_t logical_y = scroll_offset_y + i;
    if (logical_y >= buf.GetRows().size()) {
      // Print empty symbol if buffer at end
      printw("*\n");
    } else {
      // Print Row if in buffer
      Row row = buf.GetRows().at(logical_y);
      if (row.IsDirty()) {
        printw("%s", row.GetRow().c_str());
        row.SetDirty(false);
      }
    }
  }
  move(cursor.y - scroll_offset_y, cursor.x);
  refresh();
}

Renderer::~Renderer() { endwin(); }
