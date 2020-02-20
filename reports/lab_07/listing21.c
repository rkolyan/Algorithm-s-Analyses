#include "func_string.h"

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
			suffix_array[i] = length;
	}
	return SUCCESS;
}
