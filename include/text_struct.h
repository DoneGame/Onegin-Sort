#ifndef TEXT_STRUCT_H
#define TEXT_STRUCT_H

#include <stdlib.h>

struct Text_t {
    char **ptr_array;
    size_t num_lines;
    char *buffer;
    size_t buffer_size;
    size_t text_file_size;
};

#endif //TEXT_STRUCT_H
