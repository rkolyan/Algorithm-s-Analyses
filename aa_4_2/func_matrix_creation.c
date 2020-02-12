#include "func_matrix_creation.h"
#include <stdlib.h>

error_t create_matrix(int row_length, int column_length, int ***matrix)
{
	if (row_length <= 0 || column_length <= 0 || !matrix)
		return ERROR_INPUT;
	int **new_matrix = NULL;
	int *pointer = NULL;
	new_matrix = malloc(sizeof(int *) * row_length + sizeof(int) * row_length * column_length);
	if (!new_matrix)
		return ERROR_ALLOCATE;
	pointer = (int *)(new_matrix + row_length);
	for (int i = 0; i < row_length; i++)
	{
		new_matrix[i] = pointer;
		pointer += column_length;
	}
	*matrix = new_matrix;
	return SUCCESS;
}

error_t create_vinograd_array(int **matrix, int row, int col, char method, int **array)
{
	if (!matrix || !array)
		return ERROR_INPUT;
	int *new_array = NULL;
	int d = 0;
	if (method)
	{
		d = col >> 1;
		new_array = calloc(row, sizeof(int));
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < d; j++)
				new_array[i] += matrix[i][j << 1] * matrix[i][(j << 1) + 1];
		}
	}
	else
	{
		d = row >> 1;
		new_array = calloc(col, sizeof(int));
		for (int j = 0; j < col; j++)
		{
			for (int i = 0; i < d; i++)
				new_array[j] += matrix[i << 1][j] * matrix[(i << 1) + 1][j];
		}
	}
	*array = new_array;
	return SUCCESS;
}

error_t fill_random_matrix_with_size(int **matrix, int row, int col)
{
	if (row <= 0 || col <= 0 || !matrix)
		return ERROR_INPUT;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			matrix[i][j] = (int)rand();
	}
	return SUCCESS;
}
