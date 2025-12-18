#include "../include/Editor.hpp"
#include "../include/TextBuffer.hpp"

int Editor::Init()
{
    buf = (TextBuffer *)calloc(1, sizeof(TextBuffer));
    if (buf == NULL)
    {
        std::fprintf(stderr, "Error: Could not allocate buffer.\n");
        return -1;
    }
    if (init_textbuffer(buf, filename.c_str()) != 0)
    {
        return -1;
    }
    return 0;
}

void Editor::RefreshScreen()
{
    clear();
    for (size_t i = 0; i < buf->num_rows_used; i++)
    {
        printw("%s", buf->rows[i].chars);
    }
    move(cursor.y, cursor.x);
    refresh();
}

void Editor::Run()
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
