#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "main.h"
#include "input.h"
#include "sorting.h"
#include "output.h"

const char text_filename[] = "test.txt"; // onegin_en.txt


int main () {
    struct Text_t original_text = {.ptr_array = NULL, .num_lines = 0, .buffer = NULL, .buffer_size = 0, .text_file_size = 0};

    create_text_from_file (text_filename, &original_text);

    if (!original_text.num_lines)
        return 1;

    printf ("\nOriginal array of pointers before sorting:\n");
    print_pointer_array (original_text.ptr_array, original_text.num_lines);

    printf ("Original text:\n");
    print_text (original_text);


    struct Text_t bubble_sorted_text = {.ptr_array = NULL, .num_lines = original_text.num_lines, 
                                 .buffer = original_text.buffer, .buffer_size = original_text.buffer_size, 
                                 .text_file_size = original_text.text_file_size};

    printf ("\nCopying pointer array for bubble sorting\n");

    if (!bubble_sorted_text.num_lines)
        return 1;

    copy_pointer_array (&original_text, &bubble_sorted_text);

    printf ("Unsorted array of pointers:\n");
    print_pointer_array (bubble_sorted_text.ptr_array, bubble_sorted_text.num_lines);

    printf ("Bubble sorting text...\n");
    bubble_sort (bubble_sorted_text.ptr_array, bubble_sorted_text.num_lines, sizeof(char *), my_strcmp);

    printf ("\nBubble sorted array of pointers:\n");
    print_pointer_array (bubble_sorted_text.ptr_array, bubble_sorted_text.num_lines);

    printf ("Bubble sorted text:\n");
    print_text (bubble_sorted_text);


    struct Text_t quick_sorted_text = {.ptr_array = NULL, .num_lines = original_text.num_lines, 
                                       .buffer = original_text.buffer, .buffer_size = original_text.buffer_size, 
                                       .text_file_size = original_text.text_file_size};

    printf ("\nCopying pointer array for quick sorting\n");

    if (!quick_sorted_text.num_lines)
        return 1;

    copy_pointer_array (&original_text, &quick_sorted_text);

    printf ("Quick sorting text...\n");
    qsort (quick_sorted_text.ptr_array, quick_sorted_text.num_lines, sizeof(char *), my_strcmp);

    printf ("\nQuick sorted array of pointers:\n");
    print_pointer_array (quick_sorted_text.ptr_array, quick_sorted_text.num_lines);

    printf ("Quick sorted text:\n");
    print_text (quick_sorted_text);

    // printf ("Original array of pointers after sorting:\n");
    // print_pointer_array (original_text.ptr_array, original_text.num_lines);


    destroy_text (original_text);

    return 0;
}

void copy_pointer_array (struct Text_t *from_text, struct Text_t *to_text) {
    assert (from_text);
    assert (from_text->num_lines != 0);
    assert (to_text);

    to_text->num_lines = from_text->num_lines;

    create_pointer_array (to_text);

    for (size_t i = 0; i < from_text->num_lines; i++)
        to_text->ptr_array[i] = from_text->ptr_array[i];
}

void destroy_text (struct Text_t text_to_destroy) {
    free (text_to_destroy.buffer);    text_to_destroy.buffer    = NULL;
    free (text_to_destroy.ptr_array); text_to_destroy.ptr_array = NULL;
    text_to_destroy.num_lines      = 0;
    text_to_destroy.buffer_size    = 0;
    text_to_destroy.text_file_size = 0;
}
