#ifndef FUNC_SORT_H
#define FUNC_SORT_H

#include "error_codes.h"

typedef double type_t; 

error_t sort_min_max(type_t *array, int count);
error_t sort_bubble(type_t *array, int count);
error_t sort_shaker(type_t *array, int count);

#endif
