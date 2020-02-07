#include "func_matrix_creation.h"
#include <stdlib.h>

error_t create_matrix(int row_length, int column_length, double ***matrix)
{
	if (row_length <= 0 || column_length <= 0 || !matrix)
		return ERROR_INPUT;
	double **new_matrix = NULL;
	double *pointer = NULL;
	new_matrix = malloc(sizeof(double *) * row_length + sizeof(double) * row_length * column_length);
	if (!new_matrix)
		return ERROR_ALLOCATE;
	pointer = (double *)(new_matrix + row_length);
	for (int i = 0; i < row_length; i++)
	{
		new_matrix[i] = pointer;
		pointer += column_length;
	}
	*matrix = new_matrix;
	return SUCCESS;
}

error_t create_vinograd_array(double **matrix, int row, int col, char method, double **array)
{
	if (!matrix || !array)
		return ERROR_INPUT;
	double *new_array = NULL;
	int d = 0;
	if (method)
	{
		d = col >> 1;
		new_array = calloc(row, sizeof(double));
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < d; j++)
				new_array[i] += matrix[i][j << 1] * matrix[i][(j << 1) + 1];
		}
	}
	else
	{
		d = row >> 1;
		new_array = calloc(col, sizeof(double));
		for (int j = 0; j < col; j++)
		{
			for (int i = 0; i < d; i++)
				new_array[j] += matrix[i << 1][j] * matrix[(i << 1) + 1][j];
		}
	}
	*array = new_array;
	return SUCCESS;
}

error_t fill_random_matrix_with_size(double **matrix, int row, int col)
{
	if (row <= 0 || col <= 0 || !matrix)
		return ERROR_INPUT;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			matrix[i][j] = ((double)rand()) / 100000;
	}
	return SUCCESS;
}
