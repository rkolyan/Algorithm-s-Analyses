#include "func_string.h"
#include <stdio.h>
#include <string.h>

error_t is_needle_in_haystack_usual(char *haystack, int hlength, char *needle, int nlength, int *result)
{
	if (!needle || !haystack || !nlength || !hlength || !result)
		return ERROR_INPUT;

	int tmp_result = -1;

	for (int i = 0, i1 = 0, c = 0; i < hlength && tmp_result == -1; i++)
	{
		i1 = i;
		c = i;
		tmp_result = i;
		for (int j = 0; j < nlength && i1 < hlength; j++)
		{
			if (haystack[i1] != needle[j])
			{
				tmp_result = -1;
				break;
			}
			i1++;
		}
		if (tmp_result && i1 - c < nlength)
			tmp_result = -1;
	}
	*result = tmp_result;
	return SUCCESS;
}
