#ifndef OUTPUT_H
#define OUTPUT_H

#include "text_struct.h"

void print_text          (const struct Text_t text);
void print_str           (const char str_name[], const char *string);
void print_pointer_array (char **ptr_array, const size_t n_lines);

#endif //OUTPUT_H