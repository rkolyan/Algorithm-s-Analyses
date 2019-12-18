#include <stdlib.h>
#include <string.h>
#include "minimum.h"
#include "func_distance.h"

//Standard Levenstein
error_t find_levenstein_distance(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *matrix)
{
	if (!s1 || !s2 || !length1 || !length2 || !result || !matrix)
		return ERROR_INPUT;

	for (int i = 0; i < length1 + 1; i++)
		matrix[i * (length2 + 1)] = i;
	for (int j = 0; j < length2 + 1; j++)
		matrix[j] = j;

	unsigned int tmp = 0;
	for (int i = 1; i < length1 + 1; i++)
	{
		for (int j = 1; j < length2 + 1; j++)
		{
			tmp = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
			matrix[i * (length2 + 1) + j] = find_minimum(3, matrix[i * (length2 + 1) + j - 1] + 1,  matrix[(i - 1) * (length2 + 1) + j] + 1,
					matrix[(i - 1) * (length2 + 1) + j - 1] + tmp);
		}
	}
	*result = matrix[length1 * (length2 + 1) + length2];
	return SUCCESS;
}

