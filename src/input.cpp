#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "input.h"
#include "output.h"


void read_from_file (const char file_name[], struct Text_t *readed_text) {
    FILE *text_file = fopen (file_name, "r");

    if (!text_file) {
        printf ("Can't open file with text!");
        return;
    }

    size_t file_size = get_file_size(text_file);

    if (!file_size) {
        printf ("Can't get file size!");
        return;
    }

    printf ("Text file size = %d bytes\n\n", file_size);

    readed_text->text_file_size = file_size;

    readed_text->buffer_size = file_size + 1 * sizeof(char);

    printf ("Reading text from file\n");

    size_t symbols_readed = 0;
    char *text_array = read_file_to_buffer (text_file, readed_text, &symbols_readed);

    fclose(text_file);

    if (!text_array)
        return;

    printf ("Calculating number of lines\n");
    size_t n_lines = count_lines (text_array, symbols_readed);

    printf ("Number of lines = %d\n\n", n_lines);

    readed_text->num_lines = n_lines;

    printf ("Creating pointers array\n");

    char **pointer_array = (char **) calloc (n_lines, sizeof(char *));

    if (!pointer_array) {
        printf ("Failed to allocate memory for pointers array!");
        readed_text->num_lines = 0;
        return;
    }

    printf ("Pointer array = %lu\n\n", (unsigned long) pointer_array);

    readed_text->ptr_array = pointer_array;

    printf ("Filling pointers array\n");
    fill_pointer_array (readed_text, n_lines, symbols_readed);

    print_pointer_array (readed_text->ptr_array, n_lines);
}

char *read_file_to_buffer (FILE *file_with_text, struct Text_t *readed_text, size_t *symbols_readed) {
    assert (file_with_text);
    assert (readed_text);
    assert (symbols_readed);

    char *text_array = (char *) calloc (readed_text->buffer_size, 1);

    if (!text_array) {
        printf ("Failed to allocate memory for text array!");
        return NULL;
    }

    readed_text->buffer      = text_array;

    *symbols_readed = fread (text_array, 1, readed_text->text_file_size, file_with_text);

    printf ("Start of text array = %lu\n\n", (unsigned long) text_array);

    return text_array;
}

size_t count_lines (char *text_array, size_t symbols_readed) {
    size_t line_no = 0;
    char *current_symbol = text_array;
    for ( ; (current_symbol = strchr(current_symbol, '\n')) != NULL; current_symbol++) {
        // printf ("new line = %lu\n", (unsigned long) current_symbol);

        if (current_symbol < text_array + symbols_readed)
            if (*(current_symbol + 1) != '\0')
                line_no++;
    }

    return line_no + 1;
}

void fill_pointer_array (struct Text_t *readed_text, size_t num_lines, size_t symbols_readed) {
    char **pointers_array_pointer = readed_text->ptr_array;
    pointers_array_pointer[0] = readed_text->buffer;

    for (char *symbol_pointer = readed_text->buffer; (symbol_pointer = strchr(symbol_pointer, '\n')) != NULL; ) {
        printf ("new line = %lu\n", (unsigned long) symbol_pointer);

        assert (symbol_pointer > NULL && symbol_pointer < readed_text->buffer + readed_text->buffer_size / sizeof(char));

        *symbol_pointer = '\0';
        symbol_pointer++;

        if (symbol_pointer < readed_text->buffer + symbols_readed) {
            assert (pointers_array_pointer + 1 < readed_text->ptr_array + num_lines);
            *(++pointers_array_pointer) = symbol_pointer;
        }
    }
}

size_t get_file_size (FILE *file) {
    assert (file);

    int file_desc = fileno(file);

    printf ("File descriptor = %d\n", file_desc);

    if (file_desc == -1)
        return 0;

    struct stat file_info;

    if (fstat(file_desc, &file_info) != 0)
        return 0;

    return file_info.st_size;
}
