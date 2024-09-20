#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "input.h"
#include "sorting.h"
#include "output.h"
#include "text_struct.h"

const char text_filename[] = "test.txt"; // onegin_en.txt


int main () {
    struct Text_t original_text = {.ptr_array = NULL, .num_lines = 0, .buffer = NULL, .buffer_size = 0, .text_file_size = 0};

    printf ("# Reading original text from file...");
    create_text_from_file (&original_text, text_filename);

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

    copy_pointer_array (&original_text, &bubble_sorted_text);

    if (!bubble_sorted_text.num_lines)
        return 1;

    printf ("Unsorted array of pointers:\n");
    print_pointer_array (bubble_sorted_text.ptr_array, bubble_sorted_text.num_lines);

    printf ("# Bubble sorting text...\n");
    bubble_sort (bubble_sorted_text.ptr_array, bubble_sorted_text.num_lines, sizeof(char *), my_strcmp);

    printf ("\nBubble sorted array of pointers:\n");
    print_pointer_array (bubble_sorted_text.ptr_array, bubble_sorted_text.num_lines);

    printf ("Bubble sorted text:\n");
    print_text (bubble_sorted_text);


    struct Text_t quick_sorted_text = {.ptr_array = NULL, .num_lines = original_text.num_lines, 
                                       .buffer = original_text.buffer, .buffer_size = original_text.buffer_size, 
                                       .text_file_size = original_text.text_file_size};

    printf ("\nCopying pointer array for quick sorting\n");

    copy_pointer_array (&original_text, &quick_sorted_text);

    if (!quick_sorted_text.num_lines)
        return 1;

    printf ("# Quick sorting text...\n");
    qsort (quick_sorted_text.ptr_array, quick_sorted_text.num_lines, sizeof(char *), my_strcmp);

    printf ("\nQuick sorted array of pointers:\n");
    print_pointer_array (quick_sorted_text.ptr_array, quick_sorted_text.num_lines);

    printf ("Quick sorted text:\n");
    print_text (quick_sorted_text);


    printf ("\n# Sorting text by ends...\n");
    qsort (quick_sorted_text.ptr_array, quick_sorted_text.num_lines, sizeof(char *), my_inverse_strcmp);

    printf ("\nSorted by line ends array of pointers:\n");
    print_pointer_array (quick_sorted_text.ptr_array, quick_sorted_text.num_lines);

    printf ("Sorted by line ends text:\n");
    print_text (quick_sorted_text);


    // printf ("Original array of pointers after sorting:\n");
    // print_pointer_array (original_text.ptr_array, original_text.num_lines);


    destroy_text (original_text);
    destroy_text (bubble_sorted_text);
    destroy_text (quick_sorted_text);
    return 0;
}
