#include <stdlib.h>
#include <string.h>
#include "error_codes.h"
#include "minimum.h"

//Recursive versions
//{
error_t find_levenstein_distance_recursive(char *s1, char *s2, int length1, int length2, unsigned *result)
{
	if (!s1 || !s2 || !length1 || !length2 || !result)
		return ERROR_INPUT;

	if (length1 == 1 || length2 == 1)
	{
		*result = s1[length1 - 1] == s2[length2 - 1] ? 0 : 1;
		*result += abs(length2 - length1);
		return SUCCESS;
	}

	short tmp = 0;
	if (s1[length1 - 1] != s2[length2 - 1])
		tmp = 1;

	find_levenstein_distance_recursive(s1, s2, length1 - 1, length2, result);
	(*result)++;
	unsigned tmp_result = 0;
	find_levenstein_distance_recursive(s1, s2, length1, length2 - 1, &tmp_result);
	*result = find_minimum(2, *result, tmp_result + 1);
	find_levenstein_distance_recursive(s1, s2, length1 - 1, length2 - 1, &tmp_result);
	*result = find_minimum(2, *result, tmp_result + tmp);
	return SUCCESS;
}
//}

//Matrix multiplying versions
//{
error_t find_levenstein_distance_matrix_version(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *matrix)//Big Memory Version
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

error_t find_levenstein_distance_modified_matrix_version(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *main_matrix)//Big Memory Version
{
	if (!s1 || !s2 || !length1 || !length2 || !result || !main_matrix)
		return ERROR_INPUT;
	
	unsigned int *matrix = main_matrix + length2 + 1;

	for (int i = 0; i < length1 + 1; i++)
		matrix[i * (length2 + 1)] = i;
	for (int j = 0; j < length2 + 1; j++)
	{
		matrix[j] = j;
		main_matrix[j] = 0xfffffffe;
	}

	unsigned int tmp = 0;
	for (int i = 1; i < length1 + 1; i++)
	{
		for (int j = 1; j < length2 + 1; j++)
		{
			tmp = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
			matrix[i * (length2 + 1) + j] = find_minimum(4, matrix[i * (length2 + 1) + j - 1] + 1,  matrix[(i - 1) * (length2 + 1) + j] + 1,
					matrix[(i - 1) * (length2 + 1) + j - 1] + tmp, matrix[(i - 2) * (length2 + 1) + j - 1] + 1);
		}
	}

	*result = matrix[length1 * (length2 + 1) + length2];
	return SUCCESS;
}
//}

//Matrix without multiplying versions
//{
error_t find_levenstein_distance_matrix_sum_version(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *matrix)//Big Memory Version
{
	if (!s1 || !s2 || !length1 || !length2 || !result || !matrix)
		return ERROR_INPUT;

	for (int j = 0; j < length2 + 1; j++)
		matrix[j] = j;

	unsigned int tmp = 0;
	int c = length2 + 1;
	for (int i = 1; i < length1 + 1; i++)
	{
		matrix[c] = i;
		for (int j = 1; j < length2 + 1; j++)
		{
			tmp = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
			matrix[c + j] = find_minimum(3, matrix[c + j - 1] + 1,  matrix[c - length2 - 1 + j] + 1,
					matrix[c - length2 + j - 2] + tmp);
		}
		c += length2 + 1;
	}
	*result = matrix[c - 1];
	return SUCCESS;
}

error_t find_levenstein_distance_modified_matrix_sum_version(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *main_matrix)//Big Memory Version
{
	if (!s1 || !s2 || !length1 || !length2 || !result || !main_matrix)
		return ERROR_INPUT;
	
	unsigned int *matrix = main_matrix + length2 + 1;

	for (int j = 0; j < length2 + 1; j++)
	{
		matrix[j] = j;
		main_matrix[j] = 0xfffffffe;
	}

	unsigned int tmp = 0;
	int c = length2 + 1;
	for (int i = 1; i < length1 + 1; i++)
	{
		matrix[c] = i;
		for (int j = 1; j < length2 + 1; j++)
		{
			tmp = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
			matrix[c + j] = find_minimum(4, matrix[c + j - 1] + 1,  matrix[c - length2 - 1 + j] + 1,
					matrix[c - length2 + j - 2] + tmp, matrix[c - length2 - length2 + j - 3] + 1);
		}
		c += length2 + 1;
	}

	*result = matrix[c - 1];
	return SUCCESS;
}
//}

//Memory optimized versions
//{
error_t find_levenstein_distance(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *rows)//Small Memory Version
{
	if (!s1 || !s2 || !length1 || !length2 || !result || !rows)
		return ERROR_INPUT;

	unsigned int *row1 = rows;
	unsigned int *row2 = row1 + length2 + 1;

	for (int i = 0; i < length2 + 1; i++)
		row1[i] = i;

	unsigned int tmp = 0;
	for (int i = 1; i < length1 + 1; i++)
	{
		row2[0] = i;
		for (int j = 1; j < length2 + 1; j++)
		{
			if (s2[i - 1] != s1[j - 1])
				tmp = 1;
			row2[j] = find_minimum(3, row1[j] + 1, row2[j - 1] + 1, row1[j - 1] + tmp);
			tmp = 0;
		}
		memcpy(row1, row2, sizeof(unsigned int) * (length2 + 1));//array in row1 = array in row2
	}

	*result = row2[length2];
	return SUCCESS;
}

error_t find_levenstein_distance_modified(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *rows)//Small Memory Version
{
	if (!s1 || !s2 || !length1 || !length2 || !result || !rows)
		return ERROR_INPUT;

	unsigned int *row0 = rows;
	unsigned int *row1 = row0 + length2 + 1;
	unsigned int *row2 = row1 + length2 + 1;

	for (int i = 0; i < length2 + 1; i++)
	{
		row1[i] = i;
		row0[i] -= 2;
	}

	unsigned int tmp = 0;
	for (int i = 1; i < length1 + 1; i++)
	{
		row2[0] = i;
		for (int j = 1; j < length2 + 1; j++)
		{
			if (s2[i - 1] != s1[j - 1])
				tmp = 1;
			row2[j] = find_minimum(4, row1[j] + 1, row2[j - 1] + 1, row1[j - 1] + tmp, row0[j - 1] + 1);
			tmp = 0;
		}
		memcpy(row0, row1, sizeof(unsigned int) * (length2 + 1));//array in row0 = array in row1
		memcpy(row1, row2, sizeof(unsigned int) * (length2 + 1));//array in row1 = array in row2
	}

	*result = row2[length2];
	return SUCCESS;
}
//}
