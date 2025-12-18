#include "../include/TextBuffer.hpp"
#include "../include/Constants.hpp"

int init_textbuffer(TextBuffer *buf, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s.\n", filename);
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read = 0;

    buf->num_rows_used = 0;
    buf->num_rows = ROW_PREALLOCATE_COUNT;
    buf->rows = (Row *)calloc(buf->num_rows, sizeof(Row));
    if (buf->rows == NULL)
    {
        goto malloc_err;
    }

    while ((read = getline(&line, &len, file)) != EOF)
    {
        if (init_row(&buf->rows[buf->num_rows_used], line, read) != 0)
        {
            return -1;
        }
        buf->num_rows_used++;

        if (buf->num_rows_used >= buf->num_rows)
        {
            buf->num_rows += ROW_PREALLOCATE_COUNT;
            buf->rows = (Row *)realloc(buf->rows, buf->num_rows * ROW_PREALLOCATE_COUNT);
            if (buf->rows == NULL)
            {
                goto malloc_err;
            }
        }
    }
    return 0;

malloc_err:
    fprintf(stderr, "Error: Could not allocate row.\n");
    return -1;
}
