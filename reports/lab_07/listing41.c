#include "func_string.h"

static error_t fill_prefix_array(char *string, int length, int *prefix_array)
{
	if (!string || !length || !prefix_array)
		return ERROR_INPUT;
	int prefix = 0;
	prefix_array[0] = 0;
	for (int i = 1; i < length; i++)
	{
		while (prefix && string[prefix] != string[i])
			prefix = prefix_array[prefix - 1];
		if (string[prefix] == string[i])
			prefix++;
		prefix_array[i] = prefix;
	}
	return SUCCESS;
}
