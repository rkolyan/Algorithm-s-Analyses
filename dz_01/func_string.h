#ifndef FUNC_STRING_H
#define FUNC_STRING_H

#include "error_codes.h"

error_t is_needle_in_haystack_usual(char *haystack, int hlength, char *needle, int nlength, int *result);

#endif
