#include "func_string.h"

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
