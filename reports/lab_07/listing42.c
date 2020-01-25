#include "func_string.h"

error_t is_needle_in_haystack_knut_morris_prat(char *haystack, int hlength, char *needle, int nlength, 
		int *prefix_array, list_t **list_head)
{
	if (!needle || !haystack || !nlength || !hlength || !prefix_array || !list_head)
		return ERROR_INPUT;
	int prefix = 0, i = 0;
	fill_prefix_array(needle, nlength, prefix_array);
	for (i = 0; i < hlength; i++)
	{
		while (prefix && needle[prefix] != haystack[i])
			prefix = prefix_array[prefix - 1];
		if (needle[prefix] == haystack[i])
			prefix++;
		if (prefix == nlength)
		{
			add_element_to_list(list_head, i - nlength + 1);
			prefix = 0;
		}
	}
	return SUCCESS;
}
