#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

typedef struct Row
{
    size_t num_chars;
    char *chars;
} Row;

int init_row(Row* row, char* line, size_t num_chars);

