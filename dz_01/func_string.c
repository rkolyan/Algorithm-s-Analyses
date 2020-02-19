#include "func_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

error_t is_needle_in_haystack_usual(char *haystack, int hlength, char *needle, int nlength, int *result)
{
	if (!needle || !haystack || !nlength || !hlength || !result)
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
			break;
	}

	*result = tmp_result;
	return SUCCESS;
}

error_t free_strings(char ***strings, int vertice_count)
{
	if (!strings || vertice_count <= 0)
		return ERROR_INPUT;
	for (int i = 0; i < vertice_count; i++)
		free((*strings)[i]);
	free(*strings);
	*strings = NULL;
	return SUCCESS;
}
