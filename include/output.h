#ifndef OUTPUT_H
#define OUTPUT_H

#include "text_struct.h"

void print_str           (const char str_name[], const char *string, bool show_original);
void print_lines_array   (const struct Line_t *ptr_array, const size_t n_lines);

#endif //OUTPUT_H