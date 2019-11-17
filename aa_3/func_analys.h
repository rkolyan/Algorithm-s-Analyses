#ifndef FUNC_ANALYS_H
#define FUNC_ANALYS_H

#include <time.h>
#include "error_codes.h"
#include "func_forms.h"

void find_calculations(int count1, int count2, function_p function, error_t (*fill_array)(type_t *, int), const char *filename);
clock_t find_time(type_t *array, int count, function_p function);
error_t fill_random_array_with_size(type_t *array, int count);
error_t fill_sorted_array_with_size(type_t *array, int count);
error_t fill_unsorted_array_with_size(type_t *array, int count);

#endif
