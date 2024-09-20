#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "input.h"
#include "text_struct.h"


char *read_file_to_buffer (const char file_name[], struct Text_t *readed_text, size_t *symbols_readed) {
    assert (readed_text);
    assert (symbols_readed);

    FILE *file_with_text = fopen (file_name, "r");

    if (!file_with_text) {
        printf ("Can't open file with text!");
        return NULL;
    }

    size_t file_size = get_file_size(file_with_text);

    if (!file_size) {
        printf ("Can't get file size!");
        return NULL;
    }

    printf ("Text file size = %d bytes\n\n", file_size);

    readed_text->text_file_size = file_size;
    readed_text->buffer_size    = file_size + 1 * sizeof(char);

    printf ("Reading text from file\n");

    char *text_array = (char *) calloc (file_size / sizeof(char) + 1, sizeof(char));

    if (!text_array) {
        printf ("Failed to allocate memory for text array!");
        return NULL;
    }

    readed_text->buffer = text_array;

    *symbols_readed = fread (text_array, 1, readed_text->text_file_size, file_with_text);

    printf ("Beginning of text array = %lu\n\n", (unsigned long) text_array);

    fclose(file_with_text);

    return text_array;
}

size_t count_lines (char *text_array, const size_t symbols_readed) {
    assert (text_array);

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

size_t get_file_size (const FILE *file) {
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
