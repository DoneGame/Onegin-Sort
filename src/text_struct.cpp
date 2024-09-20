#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "text_struct.h"
#include "input.h"


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

    printf ("Creating pointer array\n");
    create_pointer_array (readed_text);

    printf ("Filling pointer array\n");
    fill_pointer_array (readed_text, symbols_readed);
}

void create_pointer_array (struct Text_t *readed_text) {
    char **pointer_array = (char **) calloc (readed_text->num_lines, sizeof(char *));

    if (!pointer_array) {
        printf ("Failed to allocate memory for pointers array!");
        readed_text->num_lines = 0;
        return;
    }

    printf ("Pointer array = %lu\n\n", (unsigned long) pointer_array);

    readed_text->ptr_array = pointer_array;
}

void fill_pointer_array (struct Text_t *readed_text, const size_t symbols_readed) {
    assert (readed_text);
    assert (readed_text->num_lines != 0);

    char **pointers_array_pointer = readed_text->ptr_array;
    pointers_array_pointer[0] = readed_text->buffer;

    for (char *symbol_pointer = readed_text->buffer; (symbol_pointer = strchr(symbol_pointer, '\n')) != NULL; ) {
        printf ("new line = %lu\n", (unsigned long) symbol_pointer);

        assert (symbol_pointer > NULL && symbol_pointer < readed_text->buffer + readed_text->buffer_size / sizeof(char));

        *symbol_pointer = '\0';
        symbol_pointer++;

        if (symbol_pointer < readed_text->buffer + symbols_readed) {
            assert (pointers_array_pointer + 1 < readed_text->ptr_array + readed_text->num_lines);
            *(++pointers_array_pointer) = symbol_pointer;
        }
    }
}

void copy_pointer_array (struct Text_t *from_text, struct Text_t *to_text) {
    assert (from_text);
    assert (from_text->num_lines != 0);
    assert (to_text);

    to_text->num_lines = from_text->num_lines;

    create_pointer_array (to_text);

    for (size_t i = 0; i < from_text->num_lines; i++)
        to_text->ptr_array[i] = from_text->ptr_array[i];
}

void destroy_text (struct Text_t text_to_destroy) {
    free (text_to_destroy.buffer);    text_to_destroy.buffer    = NULL;
    free (text_to_destroy.ptr_array); text_to_destroy.ptr_array = NULL;
    text_to_destroy.num_lines      = 0;
    text_to_destroy.buffer_size    = 0;
    text_to_destroy.text_file_size = 0;
}