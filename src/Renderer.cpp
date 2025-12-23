#include "../include/Renderer.hpp"
#include <curses.h>

Renderer::Renderer() {
  initscr();
  cbreak();
  noecho();
  raw();
}

int Renderer::GetInput() { return getch(); }

void Renderer::Draw(TextBuffer &buf, Coords cursor) {
  size_t i = 0;
  for (auto &row : buf.GetRows()) {
    move(i, 0);
    if (row.IsDirty()) {
      clrtoeol();
      move(i, 0);
      printw("%s", row.GetRow().c_str());
      row.SetDirty(false);
    }
    i++;
  }
  move(cursor.y, cursor.x);
  refresh();
}

Renderer::~Renderer() { endwin(); }
