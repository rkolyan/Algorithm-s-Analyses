#include "func_string.h"
#include <stdio.h>
#include <string.h>

static error_t fill_suffix_array(int *suffix_array, char *string, int length)
{
	if (!suffix_array || !string || !length)
		return ERROR_INPUT;
	char fact = 0;
	for (int i = length - 2; i > -1; i--)
	{
		if (string[i] != string[length - 1])
		{
			suffix_array[length] = length - i - 1;
			fact = 1;
			break;
		}
	}
	if (!fact)
		suffix_array[length] = length;
	for (int i = length - 1; i > -1; i--)
	{
		for (int j = i - 1; j > -(length - i); j--)
		{
			fact = 1;
			if (i > 0 && j > 0 && string[i - 1] == string[j - 1])
			{
				fact = 0;
				continue;
			}
			if (j >= 0)
			{
				for (int k = 0; k < length - i; k++)
				{
					if (string[j + k] != string[i + k])
					{
						fact = 0;
						break;
					}
				}
			}
			else
			{
				for (int k = 0; k < length - i + j; k++)
				{
					if (string[k] != string[k - j + i])
					{
						fact = 0;
						break;
					}
				}
			}
			if (fact)
			{
				suffix_array[i] = i - j;
				break;
			}
		}
		if (!fact)
		{
			suffix_array[i] = length;
			continue;
		}
	}
	return SUCCESS;
}

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
