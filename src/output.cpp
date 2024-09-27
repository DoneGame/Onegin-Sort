#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

#include "output.h"


void print_str (const char str_name[], const char *string, bool show_original) {
    assert (string);

    #ifndef NDEBUG
        printf ("%s = ", str_name);
    #endif //NDEBUG

    #ifndef NDEBUG
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
    #else
        if (show_original) {
            printf ("%s", string);
        }
        else {
            for (size_t i = 0; i < strlen(string); i++) {
                if (isalpha(string[i]))
                    printf ("%c", tolower(string[i]));
            }
        }
    #endif //NDEBUG

    printf ("\n");
}
