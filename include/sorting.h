#ifndef SORTING_H
#define SORTING_H

typedef int (*compare_func_t) (const void *a, const void *b);

void bubble_sort       (void *data, size_t size, size_t el_size, compare_func_t compare_func);
void swap              (char *first_el_pointer, char *second_el_pointer, char *tmp_pointer, size_t el_size);
int  my_strcmp         (const void *string1, const void *string2);
int  my_inverse_strcmp (const void *string1, const void *string2);

#endif //SORTING_H
