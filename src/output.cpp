#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "output.h"


void print_text (const struct Text_t text) {
    for (size_t i = 0; i < text.num_lines; i++) {
        char str_no[10] = ""; // 10 - maximum length of unsigned int in base 10
        itoa (i, str_no, 10);

        assert (i < text.num_lines);
        assert (text.ptr_array[i]);
        print_str (str_no, text.ptr_array[i]);
    }
}

void print_str (const char str_name[], const char *string) {
    assert (string);

    printf ("%s = ", str_name);
    for (size_t i = 0; i < strlen(string); i++)
        printf ("%c(%3d) ", string[i], string[i]);
    printf ("\n");
}

void print_pointer_array (char **ptr_array, const size_t n_lines) {
    assert (ptr_array);

    printf ("\nArray of pointers:\n");
    for (size_t i = 0; i < n_lines; i++) {
        assert (i < n_lines);

        printf ("Str %d = %lu\n", i, (unsigned long) ptr_array[i]);
    }
    printf ("\n");
}
