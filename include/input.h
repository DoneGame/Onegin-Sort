#ifndef INPUT_H
#define INPUT_H

#include "text_struct.h"

void     create_text_from_file (const char file_name[], struct Text_t *readed_text);
char*    read_file_to_buffer   (const char file_name[], struct Text_t *readed_text, size_t *n_symbols_readed);
unsigned count_lines           (char *text_array, const size_t symbols_readed);
void     fill_pointer_array    (struct Text_t *readed_text, const size_t symbols_readed);
size_t   get_file_size         (const FILE *file);

#endif //INPUT_H
