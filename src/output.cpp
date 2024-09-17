#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "output.h"


void print_text (struct Text text) {
    for (unsigned i = 0; i < text.num_lines; i++) {
        char str_no[10] = ""; // 10 - maximum length of unsigned int in base 10
        itoa (i, str_no, 10);

        assert (i < text.num_lines);
        assert (text.ptr_array[i]);
        print_str (str_no, text.ptr_array[i]);
    }
}

void print_str (char str_name[], const char *string) {
    printf ("%s = ", str_name);
    for (unsigned i = 0; i < strlen(string); i++)
        printf ("%c(%3d) ", string[i], string[i]);
    printf ("\n");
}
