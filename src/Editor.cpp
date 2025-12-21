#include "../include/Editor.hpp"

Editor::Editor(std::string filename) {
  buffers.emplace_back(filename);
  active_buffer = 0;
}

void Editor::RefreshScreen() {
  clear();
  for (auto row : buffers.at(active_buffer).GetLines()) {
    printw("%s", row.GetChars().c_str());
  }
  move(cursor.y, cursor.x);
  refresh();
}

void Editor::Run() {
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
    RefreshScreen();
  }
}
