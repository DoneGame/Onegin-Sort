#include <stdio.h>

#include "input.h"
#include "sorting.h"
#include "output.h"

const char text_filename[] = "test.txt"; // onegin_en.txt


int main () {
    struct Text_t original_text = {.ptr_array = NULL, .num_lines = 0, .buffer = NULL, .buffer_size = 0, .text_file_size = 0};

    read_from_file (text_filename, &original_text);

    if (!original_text.num_lines)
        return 1;

    struct Text_t sorted_text = bubble_sort (original_text);

    printf ("Sorted text:\n");
    print_text (sorted_text);

    free(original_text.buffer);    original_text.buffer    = NULL;
    free(original_text.ptr_array); original_text.ptr_array = NULL;

    return 0;
}
