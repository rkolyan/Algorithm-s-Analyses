#include "error_codes.h"
#include "func_sort.h"

error_t sort_min_max(type_t *array, int count)
{
	if (!array || count <= 0)
		return ERROR_INPUT;

	int d = count >> 1, minimum_index = 0, maximum_index = 0;
	type_t minimum = 0, maximum = 0, tmp = 0;
	for (int k = 0; k < d; k++)
	{
		minimum_index = k;
		maximum_index = count - k - 1;
		minimum = array[k];
		maximum = array[count - k - 1];
		for (int i = k; i < count - k; i++)
		{
			if (minimum > array[i])
			{
				minimum = array[i];
				minimum_index = i;
			}
			if (maximum <= array[i])
			{
				maximum = array[i];
				maximum_index = i;
			}
		}
		if (maximum_index == k)
		{
			tmp = array[k];
			array[k] = array[minimum_index];
			array[minimum_index] = array[count - k - 1];
			array[count - k - 1] = tmp;
		}
		else if (minimum_index == count - k - 1)
		{
			tmp = array[count - k - 1];
			array[count - k - 1] = array[maximum_index];
			array[maximum_index] = array[k];
			array[k] = tmp;
		}
		else
		{
			tmp = array[k];
			array[k] = array[minimum_index];
			array[minimum_index] = tmp;
			tmp = array[count - k - 1];
			array[count - k - 1] = array[maximum_index];
			array[maximum_index] = tmp;
		}
	}
	return SUCCESS;
}
