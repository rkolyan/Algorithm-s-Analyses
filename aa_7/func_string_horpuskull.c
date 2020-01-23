#include "func_string.h"
#include <string.h>

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

error_t is_needle_in_haystack_boyer_mur_horpuskul(char *haystack, int hlength, char *needle, int nlength, 
			   								      int *shift_array, list_t **list_head)
{
	if (!needle || !haystack || !nlength || !hlength || hlength < nlength || !shift_array || !list_head)
		return ERROR_INPUT;

	fill_shift_array(shift_array, needle, nlength);
	int tmp_result = 0;
	for (int i = 0; i <= hlength - nlength;)
	{
		tmp_result = i;
		for (int j = nlength - 1; j >= 0; j--)
		{
			if (needle[j] != haystack[i + j])
			{
				tmp_result = -1;
				i += shift_array[(int)haystack[i + j]];
				break;
			}
		}
		if (tmp_result != -1)
		{
			add_element_to_list(list_head, tmp_result);
			i++;
		}
	}
	return SUCCESS;
}
