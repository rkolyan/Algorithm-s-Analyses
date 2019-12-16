#include "func_matrix_creation.h"
#include <stdlib.h>

error_t create_vinograd_array(double *matrix, int row, int col, char method, double **array)
{
	if (!matrix || !array)
		return ERROR_INPUT;
	double *new_array = NULL;
	int d = 0;
	if (method)
	{
		d = col >> 1;
		new_array = calloc(row, sizeof(double));
		if (!new_array)
			return ERROR_ALLOCATE;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < d; j++)
				new_array[i] += matrix[i * col + (j << 1)] * matrix[i * col + (j << 1) + 1];
		}
	}
	else
	{
		d = row >> 1;
		new_array = calloc(col, sizeof(double));
		if (!new_array)
			return ERROR_ALLOCATE;
		for (int j = 0; j < col; j++)
		{
			for (int i = 0; i < d; i++)
				new_array[j] += matrix[(i << 1) * col + j] * matrix[((i << 1) + 1) * col + j];
		}
	}
	*array = new_array;
	return SUCCESS;
}
