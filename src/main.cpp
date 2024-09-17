#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char text_filename[] = "onegin_en.txt"; // test.txt

struct Text {
    char **ptr_array;
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
    struct Text original_text = {.ptr_array = NULL, .num_lines = 0};
    
    read_from_file (text_filename, &original_text);

    if (!original_text.num_lines)
        return 1;

    struct Text sorted_text = bubble_sort (original_text);

    print_text (sorted_text);

    free(original_text.ptr_array[0]); original_text.ptr_array[0] = NULL;
    free(original_text.ptr_array);    original_text.ptr_array = NULL;

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

    printf ("start of array = %lu\n", (unsigned long) text_array);

    printf ("Calculating number of lines\n");

    unsigned line_no = 0;
    char *current_symbol = text_array;
    for ( ; (current_symbol = strchr(current_symbol, '\n')) != NULL; current_symbol++) {
        printf ("new line = %lu\n", (unsigned long) current_symbol);

        if (current_symbol < text_array + n_symbols_readed)
            if (*(current_symbol + 1) != '\0')
                line_no++;
    }

    unsigned n_lines = line_no + 1;

    printf ("Number of lines = %d\n", n_lines);

    printf ("Creating pointers array\n");

    char **pointers_array = (char **) calloc (n_lines, sizeof(char *));

    if (!pointers_array) {
        printf ("Failed to allocate memory for pointers array!");
        return;
    }

    printf ("Pointers array = %lu\n", (unsigned long) pointers_array);

    readed_text->ptr_array = pointers_array;
    pointers_array[0] = text_array;

    for (char *symbol_pointer = text_array; (symbol_pointer = strchr(symbol_pointer, '\n')) != NULL; ) {
        printf ("new line = %lu\n", (unsigned long) symbol_pointer);

        assert (symbol_pointer > NULL && symbol_pointer < text_array + array_size / sizeof(char));

        *symbol_pointer = '\0';
        symbol_pointer++;

        if (symbol_pointer < text_array + n_symbols_readed) {
            assert (pointers_array + 1 < readed_text->ptr_array + n_lines);
            *(++pointers_array) = symbol_pointer;
        }
    }

    printf ("\nArray of pointers:\n");
    for (unsigned i = 0; i < n_lines; i++) {
        assert (i < n_lines);

        printf ("Str %d = %lu\n", i, (unsigned long) readed_text->ptr_array[i]);
    }
    printf ("\n");

    readed_text->num_lines = n_lines;

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
    assert (string1);
    assert (string2);

    int i = 0;
    for (; string1[i] != '\0' && string1[i] == string2[i]; i++) {}; 
    
    return string1[i] - string2[i];
}

void print_text (struct Text text) {
    for (unsigned i = 0; i < text.num_lines; i++) {
        char str_no[10] = "";
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
