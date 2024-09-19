#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

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
                uint64_t tmp = 0;
                char *pointer_to_tmp = (char *) &tmp;

                byte_by_byte_copy (data_ + j*el_size,        pointer_to_tmp,           el_size);
                byte_by_byte_copy (data_ + (j + 1)*el_size,  data_ + j*el_size,        el_size);
                byte_by_byte_copy (pointer_to_tmp,           data_ + (j + 1)*el_size,  el_size);
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

    size_t i = 0;
    size_t j = 0;
    while (real_string_1[i] != '\0' && real_string_2[j] != '\0') {
        if (isalpha(real_string_1[i]) && isalpha(real_string_2[j])) {
            if (tolower(real_string_1[i]) != tolower(real_string_2[j]))
                break;
            else {
                i++;
                j++;
                continue;
            }
        }

        if (!isalpha(real_string_1[i])) {
            i++;
            continue;
        }

        if (!isalpha(real_string_2[j]))
            j++;
    }
    
    return tolower(real_string_1[i]) - tolower(real_string_2[i]);
}
