#include "func_string.h"

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
