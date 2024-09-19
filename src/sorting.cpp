#include <assert.h>
#include <stdbool.h>

#include "sorting.h"
#include "output.h"


void bubble_sort (void *data, size_t size, size_t el_size, compare_func_t compare_func) {
    assert (data);
    assert (size);

    char *data_ = (char *) data;

    for (size_t i = size; i > 0; i--) {
        for (size_t j = 0; j < i - 1; j++) {
            assert (j + 1 < size);

            if (compare_func (data_ + j*el_size, data_ + (j + 1)*el_size) > 0) {
                long long tmp = 0;
                char *pointer_to_tmp = (char *) &tmp;

                byte_by_byte_copy (data_ + j*el_size, pointer_to_tmp, el_size);

                byte_by_byte_copy (data_ + (j + 1)*el_size, data_ + j*el_size, el_size);

                byte_by_byte_copy (pointer_to_tmp, data_ + (j + 1)*el_size, el_size);
            }
        }
    }
}

void byte_by_byte_copy (char *from_ptr, char *to_ptr, size_t el_size) {
    for (size_t byte_shift = 0; byte_shift < el_size; byte_shift++)
        *(to_ptr + byte_shift) = *(from_ptr + byte_shift);
}

int my_strcmp (const void *string1, const void *string2) {
    assert (string1);
    assert (string2);

    const char *real_string_1 = * (const char **) string1;
    const char *real_string_2 = * (const char **) string2;

    print_str ("str1", real_string_1);
    print_str ("str2", real_string_2);

    int i = 0;
    for (; real_string_1[i] != '\0' && real_string_1[i] == real_string_2[i]; i++) {}; 
    
    return real_string_1[i] - real_string_2[i];
}
