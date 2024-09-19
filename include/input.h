#ifndef INPUT_H
#define INPUT_H

#include "text_struct.h"

void     read_from_file      (const char file_name[], struct Text_t *readed_text);
char *   read_file_to_buffer (FILE *file_with_text, struct Text_t *readed_text, size_t *n_symbols_readed);
unsigned count_lines         (char *text_array, size_t symbols_readed);
void     fill_pointer_array  (struct Text_t *readed_text, size_t num_lines, size_t symbols_readed);
size_t   get_file_size       (FILE *file);

#endif //INPUT_H
