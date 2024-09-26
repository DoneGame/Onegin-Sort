#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "text_struct.h"
#include "input.h"
#include "output.h"


void create_text_from_file (struct Text_t *readed_text, const char file_name[]) {
    assert (readed_text);

    size_t symbols_readed = 0;
    char *text_array = read_file_to_buffer (file_name, readed_text, &symbols_readed);

    if (!text_array)
        return;

    printf ("Symbols read = %lu\n", (unsigned long) symbols_readed);

    #ifndef NDEBUG
    printf ("\nCalculating number of lines\n");
    #endif //NDEBUG
    size_t n_lines = count_lines (text_array, symbols_readed);

    printf ("Number of lines in file = %lu\n\n", (unsigned long) n_lines);

    readed_text->num_lines = n_lines;

    #ifndef NDEBUG
    printf ("Creating lines array\n");
    #endif //NDEBUG
    create_lines_array (readed_text);

    #ifndef NDEBUG
    printf ("Filling lines array\n");
    #endif //NDEBUG
    fill_lines_array (readed_text, symbols_readed);
}

void create_lines_array (struct Text_t *readed_text) {
    assert (readed_text);
    assert (readed_text->num_lines != 0);

    struct Line_t *lines_array = (struct Line_t *) calloc (readed_text->num_lines, sizeof(struct Line_t));

    if (!lines_array) {
        printf ("Failed to allocate memory for pointers array!");
        readed_text->num_lines = 0;
        return;
    }

    #ifndef NDEBUG
    printf ("Lines array = %lu\n\n", (unsigned long) lines_array);
    #endif //NDEBUG

    readed_text->lines_array = lines_array;
}

void fill_lines_array (struct Text_t *readed_text, const size_t symbols_readed) {
    assert (readed_text);
    assert (readed_text->num_lines != 0);

    struct Line_t *lines_array_pointer = readed_text->lines_array;
    lines_array_pointer[0].beginning = readed_text->buffer;
    lines_array_pointer[0].length = 0;

    for (char *symbol_pointer = readed_text->buffer; (symbol_pointer = strchr(symbol_pointer, '\n')) != NULL; ) {
        #ifndef NDEBUG
        printf ("new line = %lu\n", (unsigned long) symbol_pointer);
        #endif //NDEBUG

        assert (symbol_pointer > (char *) NULL && symbol_pointer < readed_text->buffer + readed_text->buffer_size / sizeof(char));

        *symbol_pointer = '\0';
        lines_array_pointer->length = (symbol_pointer - lines_array_pointer->beginning) / sizeof(char);
        symbol_pointer++;

        if (symbol_pointer < readed_text->buffer + symbols_readed) {
            assert (lines_array_pointer + 1 < readed_text->lines_array + readed_text->num_lines);
            (++lines_array_pointer)->beginning = symbol_pointer;
        }
    }


    struct Line_t *last_line_ptr = readed_text->lines_array + readed_text->num_lines - 1;

    assert (last_line_ptr->beginning);
    if (last_line_ptr->length == 0)
        last_line_ptr->length = (readed_text->buffer + symbols_readed - last_line_ptr->beginning) / sizeof(char);
}

void copy_lines_array (const struct Text_t from_text, struct Text_t *to_text) {
    assert (from_text.num_lines != 0);
    assert (to_text);

    to_text->num_lines = from_text.num_lines;

    create_lines_array (to_text);

    for (size_t i = 0; i < from_text.num_lines; i++)
        to_text->lines_array[i] = from_text.lines_array[i];
}

void print_text (const struct Text_t text, bool show_original) {
    assert (text.num_lines != 0);
    assert (text.lines_array);

    for (size_t i = 0; i < text.num_lines; i++) {
        char str_no[11] = ""; // 10 - maximum length of unsigned int in base 10
        sprintf(str_no, "%lu", (unsigned long) i);

        assert (i < text.num_lines);
        assert (text.lines_array[i].beginning);

        print_str (str_no, text.lines_array[i].beginning, show_original);
    }
}

void print_inverse_sorted_text (const struct Text_t text, bool show_original) {
    assert (text.num_lines != 0);
    assert (text.lines_array);

    size_t max_length = 0;

    if (show_original)
        for (size_t i = 0; i < text.num_lines; i++) {
            if (text.lines_array[i].length > max_length)
                max_length = text.lines_array[i].length;
        }
    else {
        for (size_t i = 0; i < text.num_lines; i++) {
            size_t len_cnt = 0;
            for (size_t symbol = 0; symbol < text.lines_array[i].length; symbol++) {
                if (isalpha(text.lines_array[i].beginning[symbol]))
                    len_cnt++;
            }

            if (len_cnt > max_length)
                max_length = len_cnt;
        }
    }


    for (size_t i = 0; i < text.num_lines; i++) {
        char str_no[11] = ""; // 10 - maximum length of unsigned int in base 10
        sprintf(str_no, "%lu", (unsigned long) i);

        assert (i < text.num_lines);
        assert (text.lines_array[i].beginning);

        size_t len = 0;
        if (show_original)
            len = text.lines_array[i].length;
        else {
            for (size_t symbol = 0; symbol < text.lines_array[i].length; symbol++) {
                if (isalpha(text.lines_array[i].beginning[symbol]))
                    len++;
            }
        }

        #ifndef NDEBUG
        printf ("Printable line length = %lu\n", (unsigned long) len);
        #endif //NDEBUG

        printf (" ");

        for (size_t j = 0; j < (size_t) (floor(log10(text.num_lines - 1)) + 1 - strlen(str_no)); j++) {
            printf (" ");
        }

        for (size_t j = 0; j < max_length - len; j++) {
            #ifndef NDEBUG
                printf ("       ");
            #else
                printf (" ");
            #endif //NDEBUG
        }

        print_str (str_no, text.lines_array[i].beginning, show_original);
    }
}

void destroy_text (struct Text_t *text_to_destroy) {
    text_to_destroy->buffer = NULL;
    free (text_to_destroy->lines_array); text_to_destroy->lines_array = NULL;
    text_to_destroy->num_lines   = 0;
    text_to_destroy->buffer_size = 0;
}