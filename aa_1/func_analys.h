#ifndef FUNC_ANALYS_H
#define FUNC_ANALYS_H

#include <time.h>
#include "func_forms.h"

clock_t find_time(char *s1, char *s2, int length1, int length2, function_t *functions);
char *create_random_word_with_size(int size);

#endif
