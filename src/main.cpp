#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <cstring>
#include "../include/Constants.hpp"
#include "../include/Editor.hpp"

void quit()
{
    endwin();
}

typedef struct Args
{
    std::string filename;
} Args;

int HandleArgs(Args *args, int argc, char **argv)
{
    if (argc <= 1)
    {
        std::fprintf(stderr, "Error: No file was provided.\n");
        return -1;
    }
    size_t filename_len = strlen(argv[1]);
    if (filename_len > MAX_FILENAME_LEN)
    {
        std::fprintf(stderr, "Error: Filename to long.\n");
        return -1;
    }
    args->filename = std::string(argv[1]);
    return 0;
}

int main(int argc, char **argv)
{
    Args args;
    if (HandleArgs(&args, argc, argv) != 0)
    {
        return -1;
    }
    Editor e = Editor(std::string(args.filename));
    if (e.Init() != 0)
    {
        return -1;
    }
    atexit(quit);
    initscr();

    nodelay(stdscr, TRUE);
    e.Run();

    return 0;
}
