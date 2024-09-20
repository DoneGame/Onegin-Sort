#ifndef TEXT_STRUCT_H
#define TEXT_STRUCT_H

#include <stdlib.h>

/*
struct Line_t {
    char *beginning;

};
*/

struct Text_t {
    char **ptr_array;
    size_t num_lines;
    char *buffer;
    size_t buffer_size;
    size_t text_file_size;
};


void create_text_from_file (struct Text_t *readed_text, const char file_name[]);
void create_pointer_array  (struct Text_t *readed_text);
void fill_pointer_array    (struct Text_t *readed_text, const size_t symbols_readed);
void copy_pointer_array    (struct Text_t *from_text, struct Text_t *to_text);
void destroy_text          (struct Text_t text_to_destroy);

#endif //TEXT_STRUCT_H
