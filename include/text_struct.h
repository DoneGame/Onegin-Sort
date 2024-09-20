#ifndef TEXT_STRUCT_H
#define TEXT_STRUCT_H

#include <stdlib.h>


struct Line_t {
    char *beginning;
    size_t length;
};

struct Text_t {
    struct Line_t *lines_array;
    size_t num_lines;
    char *buffer;
    size_t buffer_size;
};


void create_text_from_file (struct Text_t *readed_text, const char file_name[]);
void create_lines_array    (struct Text_t *readed_text);
void fill_lines_array      (struct Text_t *readed_text, const size_t symbols_readed);
void copy_lines_array      (struct Text_t *from_text, struct Text_t *to_text);
void print_text            (const struct Text_t text, bool show_original);
void destroy_text          (struct Text_t *text_to_destroy);

#endif //TEXT_STRUCT_H
