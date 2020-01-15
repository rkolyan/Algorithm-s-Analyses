#ifndef FUNC_STRING_H
#define FUNC_STRING_H

#include "error_codes.h"

error_t is_needle_in_haystack_usual(char *needle, int nlength, char *haystack, int hlength, int *result);
error_t is_needle_in_haystack_boyer_mur(char *needle, int nlength, char *haystack, int hlength, int *result);
error_t is_needle_in_haystack_knut_morris_prat(char *needle, int nlength, char *haystack, int hlength, int *prefix_array, int *result);

#endif
