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

/*
error_t is_needle_in_haystack_boyer_mur(char *haystack, int hlength, char *needle, int nlength, int *result)
{
	if (!needle || !haystack || !nlength || !hlength || !result)
		return ERROR_INPUT;
	*result = -1;
	int count = 0;
	for (int i = 0; i < hlength && i + nlength - 1 < hlength; i++)
	{
		if (needle[nlength - 1] == haystack[i + nlength - 1])
		{
			for (count = nlength - 2; count >= 0 && needle[count] == haystack[i + count]; count--);
			if (count == -1)
			{
				*result = i;
				break;
			}
			i += count;
		}
	}
	return SUCCESS;
}
*/

static error_t fill_shift_array(int *shift_array, char *string, int length)
{
	if (!shift_array || !string || !length)
		return ERROR_INPUT;
	for (int i = 0; i < SHIFT_ARRAY_SIZE; i++)
		shift_array[i] = -1;
	shift_array[(int)string[length - 1]] = length;
	for (int i = length - 2, index = 1; i >= 0; i--, index++)
	{
		if (shift_array[(int)string[i]] == -1)
			shift_array[(int)string[i]] = index;
	}
	for (int i = 0; i < SHIFT_ARRAY_SIZE; i++)
	{
		if (shift_array[i] == -1)
			shift_array[i] = length;
	}
	return SUCCESS;
}

//Bad symbol version
error_t is_needle_in_haystack_boyer_mur_horpuskul(char *haystack, int hlength, char *needle, int nlength, 
									    int *shift_array, int *result)
{
	if (!needle || !haystack || !nlength || !hlength || !shift_array || !result)
		return ERROR_INPUT;
	if (nlength > hlength)
	{
		*result = -1;
		return SUCCESS;
	}
	fill_shift_array(shift_array, needle, nlength);
	for (int i = 0; i <= hlength - nlength;)
	{
		*result = i;
		for (int j = nlength - 1; j >= 0; j--)
		{
			if (needle[j] != haystack[i + j])
			{
				*result = -1;
				i += shift_array[(int)haystack[i + j]];
				break;
			}
		}
		if (*result != -1)
			return SUCCESS;
	}
	return SUCCESS;
}

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
