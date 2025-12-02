#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>

#define MAX_FILENAME_LEN 128
#define ROW_PREALLOCATE_COUNT 16

typedef struct Args {
    char filename[128];
} Args;

typedef struct Row {
    size_t num_chars;
    char* chars;
} Row;

typedef struct TextBuffer {
    size_t num_rows_used;
    size_t num_rows;
    Row* rows;
} TextBuffer;

int init_textbuffer(TextBuffer* buf, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) { return -1; }

    buf->num_rows_used = 0;
    buf->num_rows = ROW_PREALLOCATE_COUNT;
    buf->rows = (Row*) malloc(sizeof(Row) * buf->num_rows);
    if (buf->rows == NULL) { return -1; }

    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        buf->rows[buf->num_rows_used].chars = line;
        buf->rows[buf->num_rows_used].num_chars = read;

        buf->num_rows_used++;
        if (buf->num_rows_used >= buf->num_rows) {
            buf->num_rows += ROW_PREALLOCATE_COUNT;
            buf->rows = (Row*) realloc(buf->rows, buf->num_rows * ROW_PREALLOCATE_COUNT);
            if (buf->rows == NULL) { return -1; }
        }
    }

    return 0;
}

typedef struct Editor {
    size_t num_bufs;
    TextBuffer* buf;
} Editor;

int init_editor(Editor* e, char* filename) {
    e->buf = (TextBuffer*) malloc(sizeof(TextBuffer));
    if (e->buf == NULL) { return -1; }

    init_textbuffer(e->buf, filename);
    return 0;
}

int run_editor(Editor* e) {
    while (getchar() != 'q') {
        for (size_t i = 0; i < e->buf->num_rows_used; i++) {

        }
    }

    return 0;
}

void quit() {
    endwin();
}

int handle_args(Args* args, int argc, char** argv) {
    if (argc <= 1) { return 0; }

    size_t filename_len = strlen(argv[1]);
    if (filename_len > MAX_FILENAME_LEN) { return -1; }

    memcpy(args->filename, argv[1], filename_len);
    return 0;
}

int main(int argc, char** argv) {
    Args args;
    handle_args(&args, argc, argv);

    Editor e;
    init_editor(&e, args.filename);
    (void)e;

    int x, y;

    initscr();
    atexit(quit);
    curs_set(0);

    refresh();

    getch();
    return(0);
}
