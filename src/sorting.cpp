#include <assert.h>
#include "sorting.h"


void bubble_sort (struct Text_t sorting_text) {
    assert (sorting_text.num_lines != 0);

    for (size_t i = sorting_text.num_lines; i > 0; i--) {
        for (size_t j = 0; j < i - 1; j++) {
            assert (j + 1 < sorting_text.num_lines);

            if (my_strcmp (sorting_text.ptr_array[j], sorting_text.ptr_array[j + 1]) > 0) {
                char *tmp = sorting_text.ptr_array[j];
                sorting_text.ptr_array[j] = sorting_text.ptr_array[j + 1];
                sorting_text.ptr_array[j + 1] = tmp;
            }
        }
    }
}

int my_strcmp (const char *string1, const char *string2) {
    assert (string1);
    assert (string2);

    int i = 0;
    for (; string1[i] != '\0' && string1[i] == string2[i]; i++) {}; 
    
    return string1[i] - string2[i];
}
