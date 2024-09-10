#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int  my_strcmp   (const char *s1, const char *s2);
void print_str   (char str_name[], const char *string);
void bubble_sort (char text[50][200], unsigned index[], unsigned n_lines);

const char text_filename[] = "onegin_en.txt";

int main () {
    FILE *text_file = fopen (text_filename, "r");

    if (!text_file) {
        printf ("Can't open file with text!");
        return 1;
    }

    /*
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    const char *text = (const char *) calloc (file_size, 1);

    if (!text) {
        printf ("Failed to allocate memory!");
        return 1;
    }
    */

    char text[50][200] = {};

    unsigned line_no = 0;
    unsigned symbol_no = 0;
    int c = '\0';
    while ((c = fgetc(text_file)) != EOF) {
        assert (line_no   < 50 );
        assert (symbol_no < 200);

        if (c == '\n') {
            if (symbol_no == 0)
                continue;

            text[line_no++][symbol_no++] = '\0';
            symbol_no = 0;
        }
        else
            text[line_no][symbol_no++] = (char) c;
    }

    if (symbol_no == 0 && line_no > 0) {
        line_no--;
    }
    else {
        assert (line_no   < 50 );
        assert (symbol_no < 200);
        text[line_no][symbol_no] = '\0';
    }
    
    unsigned num_lines = line_no + 1;

    fclose(text_file);

    unsigned *index = (unsigned *) calloc (num_lines, sizeof(unsigned));

    if (!index) {
        printf ("Failed to allocate memory!");
        return 1;
    }

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

void bubble_sort (char text[50][200], unsigned index[], unsigned n_lines) {
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
