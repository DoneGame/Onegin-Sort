#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "input.h"
#include "sorting.h"
#include "output.h"
#include "text_struct.h"

const char default_text_filename[] = "onegin_example.txt";
const bool debug = false;


int main (const int argc, const char *argv[]) {
    struct Text_t original_text = {.lines_array = NULL, .num_lines = 0, 
                                   .buffer = NULL, .buffer_size = 0};

    if (argc > 1) {
        printf ("# Reading original text from %s...\n", argv[1]);
        create_text_from_file (&original_text, argv[1]);
    }
    else {
        printf ("# Reading original text from %s...\n", default_text_filename);
        create_text_from_file (&original_text, default_text_filename);
    }

    if (!original_text.num_lines)
        return 1;
    
    if (debug) {
        printf ("\nOriginal array of lines before sorting:\n");
        print_lines_array (original_text.lines_array, original_text.num_lines);
    }
    else {
        printf ("\n");
    }

    printf ("Original text:\n");
    print_text (original_text, true, debug);


    struct Text_t bubble_sorted_text = {.lines_array = NULL, .num_lines = original_text.num_lines, 
                                        .buffer = original_text.buffer, .buffer_size = original_text.buffer_size};

    printf ("\nCopying lines array for bubble sorting\n");
    copy_lines_array (original_text, &bubble_sorted_text);

    if (!bubble_sorted_text.num_lines)
        return 1;
    
    if (debug) {
        printf ("Unsorted array of lines:\n");
        print_lines_array (bubble_sorted_text.lines_array, bubble_sorted_text.num_lines);
    }

    printf ("# Bubble sorting text...\n");
    bubble_sort (bubble_sorted_text.lines_array, bubble_sorted_text.num_lines, sizeof(struct Line_t), my_strcmp);

    if (debug) {
        printf ("\nBubble sorted array of lines:\n");
        print_lines_array (bubble_sorted_text.lines_array, bubble_sorted_text.num_lines);
    }
    else {
        printf ("\n");
    }

    printf ("Bubble sorted text (only letters):\n");
    print_text (bubble_sorted_text, false, debug);


    struct Text_t quick_sorted_text = {.lines_array = NULL, .num_lines = original_text.num_lines, 
                                       .buffer = original_text.buffer, .buffer_size = original_text.buffer_size};

    printf ("\nCopying lines array for quick sorting\n");
    copy_lines_array (original_text, &quick_sorted_text);

    if (!quick_sorted_text.num_lines)
        return 1;

    printf ("# Quick sorting text...\n");
    qsort (quick_sorted_text.lines_array, quick_sorted_text.num_lines, sizeof(struct Line_t), my_strcmp);

    if (debug) {
        printf ("\nQuick sorted array of lines:\n");
        print_lines_array (quick_sorted_text.lines_array, quick_sorted_text.num_lines);
    }
    else {
        printf ("\n");
    }

    printf ("Quick sorted text:\n");
    print_text (quick_sorted_text, true, debug);


    printf ("\n# Sorting text by ends of lines...\n");
    qsort (quick_sorted_text.lines_array, quick_sorted_text.num_lines, sizeof(struct Line_t), my_inverse_strcmp);

    if (debug) {
        printf ("\nArray of lines sorted by their ends:\n");
        print_lines_array (quick_sorted_text.lines_array, quick_sorted_text.num_lines);
    }
    else {
        printf ("\n");
    }

    printf ("Sorted by line ends text:\n");
    print_inverse_sorted_text (quick_sorted_text, true, debug);


    //printf ("\nOriginal text:\n");
    //print_text (original_text, true, debug);


    free (original_text.buffer); original_text.buffer = NULL;
    destroy_text (&original_text);
    destroy_text (&bubble_sorted_text);
    destroy_text (&quick_sorted_text);
    return 0;
}
