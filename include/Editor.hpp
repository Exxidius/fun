#pragma once
#include <string>
#include "TextBuffer.hpp"
#include <curses.h>

typedef struct Coords
{
    int x;
    int y;

    Coords(int x, int y) : x(x), y(y) {}
} Coords;

class Editor
{
public:
    Editor(std::string filename) : filename(filename) {}
    int Init();
    void Run();

private:
    void RefreshScreen();

    std::string filename;
    TextBuffer *buf;
    size_t num_bufs;
    Coords cursor = Coords(0, 0);
};
