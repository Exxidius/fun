#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "Constants.h"

typedef struct Row
{
    size_t num_chars;
    char *chars;
} Row;

int init_row(Row *row, char *line, size_t num_chars)
{
    size_t len = COLUMN_PREALLOCATE_COUNT;
    row->chars = (char *)calloc(len, sizeof(char));
    if (row->chars == NULL)
    {
        fprintf(stderr, "Error: Could not allocate row.\n");
        return -1;
    }
    row->num_chars = num_chars;
    memcpy(row->chars, line, row->num_chars);
    return 0;
}