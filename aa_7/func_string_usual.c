#include "func_string.h"
#include <stdio.h>
#include <string.h>

error_t is_needle_in_haystack_usual(char *haystack, int hlength, char *needle, int nlength, list_t **list_head)
{
	if (!needle || !haystack || !nlength || !hlength || !list_head)
		return ERROR_INPUT;

	int tmp_result = -1;

	for (int i = 0; i <= hlength - nlength; i++)
	{
		tmp_result = i;
		for (int j = 0; j < nlength; j++)
		{
			if (haystack[i + j] != needle[j])
			{
				tmp_result = -1;
				break;
			}
		}
		if (tmp_result != -1)
			add_element_to_list(list_head, tmp_result);
	}
	return SUCCESS;
}
