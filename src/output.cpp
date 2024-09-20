#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "output.h"


void print_text (const struct Text_t text) {
    assert (text.lines_array);

    for (size_t i = 0; i < text.num_lines; i++) {
        char str_no[10] = ""; // 10 - maximum length of unsigned int in base 10
        itoa (i, str_no, 10);

        assert (i < text.num_lines);
        assert (text.lines_array[i].beginning);
        print_str (str_no, text.lines_array[i].beginning);
    }
}

void print_str (const char str_name[], const char *string) {
    assert (string);

    printf ("%s = ", str_name);
    for (size_t i = 0; i < strlen(string); i++)
        printf ("%c(%3d) ", string[i], tolower(string[i]));
    printf ("\n");
}

void print_lines_array (struct Line_t *lines_array, const size_t n_lines) {
    assert (lines_array);

    for (size_t i = 0; i < n_lines; i++) {
        assert (i < n_lines);

        printf ("Str %d = %lu, len = %lu\n", i, (unsigned long) lines_array[i].beginning, (unsigned long) lines_array[i].length);
    }
    printf ("\n");
}
