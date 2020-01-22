#include "error_codes.h"
#include "func_sort.h"

error_t sort_bubble(type_t *array, int count)
{
	if (!array || count <= 0)
		return ERROR_INPUT;

	char fact = 0;
	type_t tmp = 0;
	do
	{
		fact = 0;
		for (int i = 1; i < count; i++)
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
	while (fact);
	return SUCCESS;
}
