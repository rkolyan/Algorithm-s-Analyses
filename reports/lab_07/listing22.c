#include "func_string.h"

error_t is_needle_in_haystack_boyer_mur(char *haystack, int hlength, char *needle, int nlength, 
		int *suffix_array, list_t **list_head)
{
	if (!haystack || !needle || !hlength || !nlength || !suffix_array || !list_head)
		return ERROR_INPUT;
	fill_suffix_array(suffix_array, needle, nlength);
	int j = 0;
	for (int i = 0; i <= hlength - nlength;)
	{
		for (j = nlength - 1; j >= 0 && needle[j] == haystack[i + j]; j--);
		if (j < 0)
			add_element_to_list(list_head, i);
		i += suffix_array[j + 1];
	}
	return SUCCESS;
}
