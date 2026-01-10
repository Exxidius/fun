#include "../include/editor.h"
#include <algorithm>
#include <curses.h>
#include <iostream>

Editor::Editor(std::string filename) {
  buffers.emplace_back(filename);
  active_buffer_idx = 0;
  renderer.Draw(ActiveBuffer(), cursor, scroll_offset_y);
}

TextBuffer &Editor::ActiveBuffer() {
  if (active_buffer_idx < 0) {
    throw std::runtime_error("No Buffer active!");
  }
  return buffers.at(active_buffer_idx);
}

void Editor::ClampCursor() {
  cursor.y = std::clamp(cursor.y, 0, (int)ActiveBuffer().NumRows() - 1);
  cursor.x = std::clamp(cursor.x, 0, (int)ActiveBuffer().NumCharsAt(cursor.y));
}

void Editor::UpdateScrollOffset() {
  ScreenSize win = renderer.GetScreenSize();
  if (cursor.y < scroll_offset_y) {
    scroll_offset_y = cursor.y;
  }
  if (cursor.y >= scroll_offset_y + win.rows) {
    scroll_offset_y = cursor.y - win.rows + 1;
  }
}

void Editor::Run() {
  while (running) {
    int c = renderer.GetInput();
    switch (mode) {
    case EditorMode::Typing:
      HandleTyping(c);
      break;
    case EditorMode::Standard:
      HandleStandard(c);
      break;
    }
    ClampCursor();
    UpdateScrollOffset();
    renderer.Draw(ActiveBuffer(), cursor, scroll_offset_y);
  }
}

void Editor::HandleStandard(const int input) {
  StandardAction action = GetStandardAction(input);
  switch (action) {
  case StandardAction::Quit:
    running = false;
    break;
  case StandardAction::Save:
    ActiveBuffer().Save();
    break;
  case StandardAction::MoveLeft:
    cursor.x--;
    break;
  case StandardAction::MoveDown:
    cursor.y++;
    break;
  case StandardAction::MoveUp:
    cursor.y--;
    break;
  case StandardAction::MoveRight:
    cursor.x++;
    break;
  case StandardAction::EnterInsertMode:
    ChangeCursor(CursorMode::Bar);
    mode = EditorMode::Typing;
    break;
  case StandardAction::Unknown:
    break;
  }
}

void Editor::HandleTyping(const int input) {
  TypingAction action = GetTypingAction(input);
  switch (action) {
  case TypingAction::ExitTypingMode:
    ChangeCursor(CursorMode::Block);
    mode = EditorMode::Standard;
    break;
  case TypingAction::DeletePreviousChar:
    ActiveBuffer().DeleteChar(cursor);
    break;
  case TypingAction::TypeNewline:
    ActiveBuffer().InputChar('\n', cursor);
    break;
  case TypingAction::TypeCharacter:
    ActiveBuffer().InputChar(input, cursor);
    break;
  }
}

void Editor::ChangeCursor(CursorMode shape) {
  std::cout << "\033[" << shape << " q" << std::flush;
}

StandardAction Editor::GetStandardAction(const int input) {
  switch (input) {
  case 'q':
    return StandardAction::Quit;
  case CTRL_KEY('s'):
    return StandardAction::Save;
  case 'h':
    return StandardAction::MoveLeft;
  case 'j':
    return StandardAction::MoveDown;
  case 'k':
    return StandardAction::MoveUp;
  case 'l':
    return StandardAction::MoveRight;
  case 'i':
    return StandardAction::EnterInsertMode;
  default:
    return StandardAction::Unknown;
  };
}

TypingAction Editor::GetTypingAction(const int input) {
  switch (input) {
  case KEY_ESC:
    return TypingAction::ExitTypingMode;
  case KEY_BACKSPACE_ASCII:
  case KEY_BACKSPACE_DEL:
  case KEY_BACKSPACE:
    return TypingAction::DeletePreviousChar;
  case KEY_ENTER_CARR_RET:
  case KEY_ENTER_LINE_FEED:
  case KEY_ENTER:
    return TypingAction::TypeNewline;
  default:
    return TypingAction::TypeCharacter;
  };
}
