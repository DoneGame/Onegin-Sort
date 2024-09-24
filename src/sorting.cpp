#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "sorting.h"
#include "text_struct.h"


void bubble_sort (void *data, size_t size, size_t el_size, compare_func_t compare_func) {
    assert (data);
    assert (size);
    assert (el_size);

    char *data_ = (char *) data;
    char *tmp_pointer = (char *) calloc (1, el_size);

    for (size_t i = size; i > 0; i--) {
        for (size_t j = 0; j < i - 1; j++) {
            assert (j + 1 < size);

            if (compare_func (data_ + j*el_size, data_ + (j + 1)*el_size) > 0) {
                swap (data_ + j*el_size, data_ + (j + 1)*el_size, tmp_pointer, el_size);
            }
        }
    }

    free (tmp_pointer); tmp_pointer = NULL;
}

void swap (char *first_el_pointer, char *second_el_pointer, char *tmp_pointer, size_t el_size) {
    assert (first_el_pointer);
    assert (second_el_pointer);
    assert (tmp_pointer);

    //      to                 from
    memcpy (tmp_pointer,       first_el_pointer,  el_size);
    memcpy (first_el_pointer,  second_el_pointer, el_size);
    memcpy (second_el_pointer, tmp_pointer,       el_size);
}

int my_strcmp (const void *string1, const void *string2) {
    assert (string1);
    assert (string2);

    const Line_t line_1 = * (const Line_t *) string1;
    const Line_t line_2 = * (const Line_t *) string2;

    const char *real_string_1 = line_1.beginning;
    const char *real_string_2 = line_2.beginning;

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
    
    return tolower(real_string_1[i]) - tolower(real_string_2[j]);
}

int my_inverse_strcmp (const void *string1, const void *string2) {
    assert (string1);
    assert (string2);

    const Line_t line_1 = * (const Line_t *) string1;
    const Line_t line_2 = * (const Line_t *) string2;

    const char *real_string_1 = line_1.beginning;
    const char *real_string_2 = line_2.beginning;

    size_t str_1_len = line_1.length;
    size_t str_2_len = line_2.length;

    size_t i = str_1_len - 1;
    size_t j = str_2_len - 1;
    while (true) {
        assert (i < str_1_len);
        assert (j < str_2_len);

        if (isalpha(real_string_1[i]) && isalpha(real_string_2[j])) {
            if (tolower(real_string_1[i]) != tolower(real_string_2[j]))
                break;
            else {
                if (i == 0)
                    return -1;

                if (j == 0)
                    return 1;

                i--;
                j--;
                continue;
            }
        }

        assert (i < str_1_len);
        if (!isalpha(real_string_1[i])) {
            if (i == 0)
                return -1;

            i--;
            continue;
        }

        assert (j < str_2_len);
        if (!isalpha(real_string_2[j])) {
            if (j == 0)
                return 1;
             
            j--;
        }
    }

    assert (i <= str_1_len);
    assert (j <= str_2_len);
    
    return tolower(real_string_1[i]) - tolower(real_string_2[j]);
}
