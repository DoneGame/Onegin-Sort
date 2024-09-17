#ifndef INPUT_H
#define INPUT_H

#include "text_struct.h"

void   read_from_file (const char file_name[], struct Text *readed_text);
size_t get_file_size  (FILE *file);

#endif //INPUT_H
