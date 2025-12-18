#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>

#define MAX_FILENAME_LEN 128
#define ROW_PREALLOCATE_COUNT 16
#define COLUMN_PREALLOCATE_COUNT 128

typedef struct Row {
    ssize_t num_chars;
    char* chars;
} Row;

int init_row(Row* row, char* line, ssize_t num_chars) {
    size_t len = COLUMN_PREALLOCATE_COUNT;
    row->chars = (char*) calloc(len, sizeof(char));
    if (row->chars == NULL) {
        fprintf(stderr, "Could not allocate row.\n");
        return -1;
    }
    row->num_chars = num_chars;
    memcpy(row->chars, line, row->num_chars);
    return 0;
}

typedef struct TextBuffer {
    size_t num_rows_used;
    size_t num_rows;
    Row* rows;
} TextBuffer;

int init_textbuffer(TextBuffer* buf, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open the provided file.\n");
        return -1;
    }

    buf->num_rows_used = 0;
    buf->num_rows = ROW_PREALLOCATE_COUNT;
    buf->rows = (Row*) calloc(buf->num_rows, sizeof(Row));
    if (buf->rows == NULL) {
        goto malloc_err;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    while ((read = getline(&line, &len, file)) != EOF) {
        if (init_row(&buf->rows[buf->num_rows_used], line, read) != 0) { return -1; }
        buf->num_rows_used++;

        if (buf->num_rows_used >= buf->num_rows) {
            buf->num_rows += ROW_PREALLOCATE_COUNT;
            buf->rows = (Row*) realloc(buf->rows, buf->num_rows * ROW_PREALLOCATE_COUNT);
            if (buf->rows == NULL) {
                goto malloc_err;
            }
        }
    }
    return 0;

malloc_err:
    fprintf(stderr, "Could not allocate row.\n");
    return -1;
}

typedef struct Coords {
    int x;
    int y;
} Coords;

typedef struct Editor {
    size_t num_bufs;
    TextBuffer* buf;
    Coords cursor;
} Editor;

int init_editor(Editor* e, char* filename) {
    e->buf = (TextBuffer*) calloc(1, sizeof(TextBuffer));
    if (e->buf == NULL) {
        fprintf(stderr, "Could not allocate buffer.\n");
        return -1;
    }
    if (init_textbuffer(e->buf, filename) != 0) { return -1; }
    e->cursor.x = 0;
    e->cursor.y = 0;
    return 0;
}

void refresh_editor(Editor e) {
    clear();
    for (size_t i = 0; i < e.buf->num_rows_used; i++) {
        printw("%s", e.buf->rows[i].chars);
    }
    move(e.cursor.y, e.cursor.x);
    refresh();
}

void run_editor(Editor* e) {
    while (true) {
        char action = getch();
        if (action == 'q') { return; }

        switch(action) {
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

void quit() {
    endwin();
}

typedef struct Args {
    char filename[128];
} Args;

int handle_args(Args* args, int argc, char** argv) {
    if (argc <= 1) {
        fprintf(stderr, "No file was provided.\n");
        return -1;
    }
    size_t filename_len = strlen(argv[1]);
    if (filename_len > MAX_FILENAME_LEN) {
        fprintf(stderr, "Filename to long.\n");
        return -1;
    }
    memcpy(args->filename, argv[1], filename_len);
    return 0;
}

int main(int argc, char** argv) {
    Args args;
    if (handle_args(&args, argc, argv) != 0) { return -1; }
    Editor e;
    if (init_editor(&e, args.filename) != 0) { return -1; }
    atexit(quit);
    initscr();
    nodelay(stdscr, TRUE);
    run_editor(&e);
    return 0;
}

