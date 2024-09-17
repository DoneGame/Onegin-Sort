#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char text_filename[] = "onegin_en.txt"; // test.txt
const unsigned max_lines = 50;

struct Text {
    char *ptr_array[max_lines];
    unsigned num_lines;
/*
    char *buffer;
    size_t buffer_size;
    size_t file_size;
*/
};

void        read_from_file (const char file_name[], struct Text *readed_text);
struct Text bubble_sort    (struct Text sorting_text);
int         my_strcmp      (const char *s1, const char *s2);
void        print_text     (struct Text text);
void        print_str      (char str_name[], const char *string);
size_t      get_file_size  (FILE *file);


int main () {
    struct Text original_text = {.ptr_array = {NULL}, .num_lines = 0};
    
    read_from_file (text_filename, &original_text);

    if (!original_text.num_lines)
        return 1;

    struct Text sorted_text = bubble_sort (original_text);

    print_text (sorted_text);

    free(original_text.ptr_array[0]); original_text.ptr_array[0] = NULL;

    return 0;
}

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

    size_t array_size = file_size + 1 * sizeof(char);
    char *text_array = (char *) calloc (array_size, 1);

    if (!text_array) {
        printf ("Failed to allocate memory for text array!");
        return;
    }

    unsigned n_symbols_readed = fread (text_array, 1, file_size, text_file);

    readed_text->ptr_array[0] = text_array;

    printf ("start of array = %lu\n", (unsigned long) text_array);

    char *current_symbol = text_array;
    unsigned line_no = 0;
    while ((current_symbol = strchr(current_symbol, '\n')) != NULL) {
        printf ("new line = %lu\n", (unsigned long) current_symbol);

        assert (current_symbol > NULL && current_symbol < text_array + array_size / sizeof(char));

        *current_symbol = '\0';
        current_symbol++;

        if (current_symbol < text_array + n_symbols_readed) {
            assert (line_no + 1 < max_lines);
            readed_text->ptr_array[line_no + 1] = current_symbol;

            line_no++;
        }
    }

    printf ("Array of pointers:\n");
    for (unsigned i = 0; i < line_no + 1; i++) {
        assert (i < max_lines);

        printf ("Str %d = %lu\n", i, (unsigned long) readed_text->ptr_array[i]);
    }

    /*
    for (current_symbol += 1; current_symbol < text_array + text_size / sizeof(char); current_symbol++) {
        assert (current_symbol < text_array + array_size / sizeof(char));

        if (current_symbol )
    }

    if (*current_symbol != )
    */

    readed_text->num_lines = line_no + 1;

    printf ("Number of lines = %d\n", readed_text->num_lines);

    fclose(text_file);
}

struct Text bubble_sort (struct Text sorting_text) {
    for (unsigned i = sorting_text.num_lines; i > 0; i--) {
        for (unsigned j = 0; j < i - 1; j++) {
            assert (j + 1 < sorting_text.num_lines);

            if (my_strcmp (sorting_text.ptr_array[j], sorting_text.ptr_array[j + 1]) > 0) {
                char *tmp = sorting_text.ptr_array[j];
                sorting_text.ptr_array[j] = sorting_text.ptr_array[j + 1];
                sorting_text.ptr_array[j + 1] = tmp;
            }
        }
    }

    return sorting_text;
}

int my_strcmp (const char *string1, const char *string2) {
    int i = 0;
    for (; string1[i] != '\0' && string1[i] == string2[i]; i++) {}; 
    
    return string1[i] - string2[i];
}

void print_text (struct Text text) {
    for (unsigned i = 0; i < text.num_lines; i++) {
        char str_no[10] = "";
        itoa (i, str_no, 10);
        print_str (str_no, text.ptr_array[i]);
    }
}

void print_str (char str_name[], const char *string) {
    printf ("%s = ", str_name);
    for (unsigned i = 0; i < strlen(string); i++)
        printf ("%c(%3d) ", string[i], string[i]);
    printf ("\n");
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
