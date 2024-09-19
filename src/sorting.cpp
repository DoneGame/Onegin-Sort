#include <assert.h>
#include "sorting.h"


struct Text_t bubble_sort (struct Text_t sorting_text) {
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
