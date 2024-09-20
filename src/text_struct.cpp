#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "text_struct.h"
#include "input.h"
#include "output.h"


void create_text_from_file (struct Text_t *readed_text, const char file_name[]) {
    assert (readed_text);

    size_t symbols_readed = 0;
    char *text_array = read_file_to_buffer (file_name, readed_text, &symbols_readed);

    if (!text_array)
        return;

    printf ("Calculating number of lines\n");
    size_t n_lines = count_lines (text_array, symbols_readed);

    printf ("Number of lines = %d\n\n", n_lines);

    readed_text->num_lines = n_lines;

    printf ("Creating lines array\n");
    create_lines_array (readed_text);

    printf ("Filling lines array\n");
    fill_lines_array (readed_text, symbols_readed);
}

void create_lines_array (struct Text_t *readed_text) {
    struct Line_t *lines_array = (struct Line_t *) calloc (readed_text->num_lines, sizeof(struct Line_t));

    if (!lines_array) {
        printf ("Failed to allocate memory for pointers array!");
        readed_text->num_lines = 0;
        return;
    }

    printf ("Line array = %lu\n\n", (unsigned long) lines_array);

    readed_text->lines_array = lines_array;
}

void fill_lines_array (struct Text_t *readed_text, const size_t symbols_readed) {
    assert (readed_text);
    assert (readed_text->num_lines != 0);

    struct Line_t *lines_array_pointer = readed_text->lines_array;
    lines_array_pointer[0].beginning = readed_text->buffer;
    lines_array_pointer[0].length = 0;

    for (char *symbol_pointer = readed_text->buffer; (symbol_pointer = strchr(symbol_pointer, '\n')) != NULL; ) {
        printf ("new line = %lu\n", (unsigned long) symbol_pointer);

        assert (symbol_pointer > NULL && symbol_pointer < readed_text->buffer + readed_text->buffer_size / sizeof(char));

        *symbol_pointer = '\0';
        (*lines_array_pointer).length = (symbol_pointer - (*lines_array_pointer).beginning) / sizeof(char);
        symbol_pointer++;

        if (symbol_pointer < readed_text->buffer + symbols_readed) {
            assert (lines_array_pointer + 1 < readed_text->lines_array + readed_text->num_lines);
            (*(++lines_array_pointer)).beginning = symbol_pointer;
        }
    }

    struct Line_t *last_line_ptr = readed_text->lines_array + readed_text->num_lines - 1;
    assert ((*last_line_ptr).beginning);
    if (last_line_ptr->length == 0)
        last_line_ptr->length = (readed_text->buffer + symbols_readed - last_line_ptr->beginning) / sizeof(char);
}

void copy_lines_array (struct Text_t *from_text, struct Text_t *to_text) {
    assert (from_text);
    assert (from_text->num_lines != 0);
    assert (to_text);

    to_text->num_lines = from_text->num_lines;

    create_lines_array (to_text);

    for (size_t i = 0; i < from_text->num_lines; i++)
        to_text->lines_array[i] = from_text->lines_array[i];
}

void destroy_text (struct Text_t text_to_destroy) {
    free (text_to_destroy.buffer);      text_to_destroy.buffer    = NULL;
    free (text_to_destroy.lines_array); text_to_destroy.lines_array = NULL;
    text_to_destroy.num_lines   = 0;
    text_to_destroy.buffer_size = 0;
}