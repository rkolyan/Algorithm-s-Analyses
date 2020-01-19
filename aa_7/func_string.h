#ifndef FUNC_STRING_H
#define FUNC_STRING_H

#include "error_codes.h"

#define SHIFT_ARRAY_SIZE 256

error_t is_needle_in_haystack_usual(char *needle, int nlength, char *haystack, int hlength, int *result);
error_t is_needle_in_haystack_boyer_mur_horpuskul(char *needle, int nlength, char *haystack, int hlength, int *shift_array, int *result);
error_t is_needle_in_haystack_boyer_mur(char *haystack, int hlength, char *needle, int nlength, 
			   							int *shift_array, int *suffix_array, int *result);
error_t is_needle_in_haystack_knut_morris_prat(char *needle, int nlength, char *haystack, int hlength, int *prefix_array, int *result);

#endif
