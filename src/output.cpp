#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

#include "output.h"


void print_str (const char str_name[], const char *string, bool show_original) {
    assert (string);

    printf ("%s = ", str_name);

    if (show_original) {
        for (size_t i = 0; i < strlen(string); i++)
            printf ("%c(%3d) ", string[i], string[i]);
    }
    else {
        for (size_t i = 0; i < strlen(string); i++) {
            if (isalpha(string[i]))
                printf ("%c(%3d) ", tolower(string[i]), tolower(string[i]));
        }
    }

    printf ("\n");
}

void print_lines_array (const struct Line_t *lines_array, const size_t n_lines) {
    assert (lines_array);

    for (size_t i = 0; i < n_lines; i++) {
        assert (i < n_lines);

        printf ("Str %d = %lu, len = %lu\n", i, (unsigned long) lines_array[i].beginning, (unsigned long) lines_array[i].length);
    }
    printf ("\n");
}
