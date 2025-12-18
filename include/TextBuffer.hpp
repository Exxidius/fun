#pragma once
#include <stdio.h>
#include "Row.hpp"

typedef struct TextBuffer
{
    size_t num_rows_used;
    size_t num_rows;
    Row *rows;
} TextBuffer;

int init_textbuffer(TextBuffer*, const char* filename);
