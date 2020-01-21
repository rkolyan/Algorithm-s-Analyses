#include "func_string.h"
#include <stdio.h>
#include <string.h>

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

//Prefix version
error_t is_needle_in_haystack_knut_morris_prat(char *haystack, int hlength, char *needle, int nlength, 
											   int *prefix_array, int *result)
{
	if (!needle || !haystack || !nlength || !hlength || !prefix_array || !result)
		return ERROR_INPUT;
	int prefix = 0, i = 0;
	*result = -1;
	fill_prefix_array(needle, nlength, prefix_array);
	for (i = 0; i < hlength && prefix != nlength; i++)
	{
		while (prefix && needle[prefix] != haystack[i])
			prefix = prefix_array[prefix - 1];
		if (needle[prefix] == haystack[i])
			prefix++;
	}
	if (prefix == nlength)
		*result = i - nlength;
	return SUCCESS;
}
