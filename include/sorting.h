#ifndef SORTING_H
#define SORTING_H

#include "text_struct.h"

typedef int (*compare_func_t) (const void *a, const void *b);

void bubble_sort       (void *data, size_t size, size_t el_size, compare_func_t compare_func);
void byte_by_byte_copy (char *from_ptr, char *to_ptr, size_t el_size);
int  my_strcmp         (const void *string1, const void *string2);

#endif //SORTING_H
