#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <cstring>
#include "../include/Constants.h"
#include "../include/Editor.h"

void quit()
{
    endwin();
}

typedef struct Args
{
    char filename[128];
} Args;

int handle_args(Args *args, int argc, char **argv)
{
    if (argc <= 1)
    {
        fprintf(stderr, "Error: No file was provided.\n");
        return -1;
    }
    size_t filename_len = strlen(argv[1]);
    if (filename_len > MAX_FILENAME_LEN)
    {
        fprintf(stderr, "Error: Filename to long.\n");
        return -1;
    }
    memcpy(args->filename, argv[1], filename_len);
    return 0;
}

int main(int argc, char **argv)
{
    Args args;
    if (handle_args(&args, argc, argv) != 0)
    {
        return -1;
    }
    Editor e = Editor(std::string(args.filename));
    if (init_editor(&e, args.filename) != 0)
    {
        return -1;
    }
    atexit(quit);
    initscr();
    nodelay(stdscr, TRUE);
    run_editor(&e);
    return 0;
}
