#include <string>
#include "TextBuffer.h"
#include <curses.h>

typedef struct Coords
{
    int x;
    int y;
} Coords;

class Editor
{
public:
    Editor(std::string filename) {}

    void run() {}

    TextBuffer *buf;
    size_t num_bufs;
    Coords cursor;
};

int init_editor(Editor *e, char *filename)
{
    e->buf = (TextBuffer *)calloc(1, sizeof(TextBuffer));
    if (e->buf == NULL)
    {
        fprintf(stderr, "Error: Could not allocate buffer.\n");
        return -1;
    }
    if (init_textbuffer(e->buf, filename) != 0)
    {
        return -1;
    }
    e->cursor.x = 0;
    e->cursor.y = 0;
    return 0;
}

void refresh_editor(Editor e)
{
    clear();
    for (size_t i = 0; i < e.buf->num_rows_used; i++)
    {
        printw("%s", e.buf->rows[i].chars);
    }
    move(e.cursor.y, e.cursor.x);
    refresh();
}

void run_editor(Editor *e)
{
    while (true)
    {
        char action = getch();
        if (action == 'q')
        {
            return;
        }

        switch (action)
        {
        case 'h':
            e->cursor.x--;
            break;
        case 'j':
            e->cursor.y++;
            break;
        case 'k':
            e->cursor.y--;
            break;
        case 'l':
            e->cursor.x++;
            break;
        }
        refresh_editor(*e);
    }
}
