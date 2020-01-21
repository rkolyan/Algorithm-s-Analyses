#include "error_codes.h"
#include "func_sort.h"

error_t sort_shaker(type_t *array, int count)
{
	if (!array || count <= 0)
		return ERROR_INPUT;

	char fact = 1;
	int d = count >> 1;
	type_t tmp = 0;
	for (int k = 0; k < d && fact; k++)
	{
		fact = 0;
		for (int i = k + 1; i < count - k; i++)
		{
			if (array[i] < array[i - 1])
			{
				tmp = array[i];
				array[i] = array[i - 1];
				array[i - 1] = tmp;
				fact = 1;
			}
		}
		if (fact)
		{
			fact = 0;
			for (int i = count - k - 1; i > k; i--)
			{
				if (array[i] < array[i - 1])
				{
					tmp = array[i];
					array[i] = array[i - 1];
					array[i - 1] = tmp;
					fact = 1;
				}
			}
		}
	}
	return SUCCESS;
}
