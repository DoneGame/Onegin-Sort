#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "input.h"


void read_from_file (const char file_name[], struct Text *readed_text) {
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

    printf ("Text file size = %d bytes\n", file_size);

    readed_text->text_file_size = file_size;

    size_t array_size = file_size + 1 * sizeof(char);
    char *text_array = (char *) calloc (array_size, 1);

    if (!text_array) {
        printf ("Failed to allocate memory for text array!");
        return;
    }

    readed_text->buffer_size = array_size;
    readed_text->buffer      = text_array;

    unsigned n_symbols_readed = fread (text_array, 1, file_size, text_file);

    printf ("start of array = %lu\n\n", (unsigned long) text_array);

    printf ("Calculating number of lines\n");

    unsigned line_no = 0;
    char *current_symbol = text_array;
    for ( ; (current_symbol = strchr(current_symbol, '\n')) != NULL; current_symbol++) {
        // printf ("new line = %lu\n", (unsigned long) current_symbol);

        if (current_symbol < text_array + n_symbols_readed)
            if (*(current_symbol + 1) != '\0')
                line_no++;
    }

    unsigned n_lines = line_no + 1;

    printf ("Number of lines = %d\n\n", n_lines);

    printf ("Creating pointers array\n");

    char **pointers_array = (char **) calloc (n_lines, sizeof(char *));

    if (!pointers_array) {
        printf ("Failed to allocate memory for pointers array!");
        return;
    }

    printf ("Pointers array = %lu\n\n", (unsigned long) pointers_array);

    readed_text->ptr_array = pointers_array;
    pointers_array[0] = text_array;

    printf ("Filling pointers array\n");

    for (char *symbol_pointer = text_array; (symbol_pointer = strchr(symbol_pointer, '\n')) != NULL; ) {
        printf ("new line = %lu\n", (unsigned long) symbol_pointer);

        assert (symbol_pointer > NULL && symbol_pointer < text_array + array_size / sizeof(char));

        *symbol_pointer = '\0';
        symbol_pointer++;

        if (symbol_pointer < text_array + n_symbols_readed) {
            assert (pointers_array + 1 < readed_text->ptr_array + n_lines);
            *(++pointers_array) = symbol_pointer;
        }
    }

    printf ("\nArray of pointers:\n");
    for (unsigned i = 0; i < n_lines; i++) {
        assert (i < n_lines);

        printf ("Str %d = %lu\n", i, (unsigned long) readed_text->ptr_array[i]);
    }
    printf ("\n");

    fclose(text_file);

    readed_text->num_lines = n_lines;
}

size_t get_file_size (FILE *file) {
    int file_desc = fileno(file);

    printf ("File descriptor = %d\n", file_desc);

    if (file_desc == -1)
        return 0;

    struct stat file_info;

    if (fstat(file_desc, &file_info) != 0)
        return 0;

    return file_info.st_size;
}
