#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int  my_strcmp   (const char *s1, const char *s2);
void print_str   (char str_name[], const char *string);
void bubble_sort (const char text[10][10], unsigned index[], unsigned n_lines);

const char text_filename[] = "onegin_eng.txt";

int main () {
    //FILE *text_file = fopen (text_filename, "r");

    const char text[10][10] = {
        {'a', 'b', 'c', '\0'},
        {'a', 'b', 'b', '\0'},
        {'b', 'c', 'c', '\0'},
        {'a', 'a', 'a', '\0'},
        {'a', 'a', 'a', 'a', '\0'},
        {'a', 'a', 'a', 'a', 's', '\0'}
    };

    unsigned num_lines = 6;

    //fclose(text_file);

    unsigned *index = (unsigned *) calloc (num_lines, sizeof(unsigned));
    for (unsigned i = 0; i < num_lines; i++)
        index[i] = i;

    bubble_sort (text, index, num_lines);

    for (unsigned i = 0; i < num_lines; i++) {
        char str_no[10] = "";
        itoa (i, str_no, 10);
        print_str (str_no, text[index[i]]);
    }

    return 0;
}

void bubble_sort (const char text[10][10], unsigned index[], unsigned n_lines) {
    for (unsigned i = n_lines; i > 0; i--) {
        for (unsigned j = 0; j < i - 1; j++) {
            assert (j + 1 < n_lines);

            if (my_strcmp (text[index[j]], text[index[j + 1]]) > 0) {
                unsigned tmp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = tmp;
            }
        }
    }
}

int my_strcmp (const char *string1, const char *string2) {
    int i = 0;
    for (; string1[i] != '\0' && string1[i] == string2[i]; i++) {}; 
    
    return string1[i] - string2[i];
}

void print_str (char str_name[], const char *string) {
    printf ("%s = ", str_name);
    for (unsigned i = 0; i < strlen(string); i++)
        printf ("%c(%3d) ", string[i], string[i]);
    printf ("\n");
}
