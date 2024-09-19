#ifndef MAIN_H
#define MAIN_H

#include "text_struct.h"

void copy_pointer_array (struct Text_t *from_text, struct Text_t *to_text);
void destroy_text       (struct Text_t text_to_destroy);

#endif //MAIN_H