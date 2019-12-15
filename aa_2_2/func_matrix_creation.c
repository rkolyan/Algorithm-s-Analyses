#include "func_matrix_creation.h"
#include <stdlib.h>

error_t create_matrix(int row_length, int column_length, double ***matrix)
{
	if (row_length <= 0 || column_length <= 0 || !matrix)
		return ERROR_INPUT;
	double **new_matrix = NULL;
	double *pointer = NULL;
	new_matrix = malloc(sizeof(double *) * row_length + sizeof(double) * row_length * column_length);
	pointer = (double *)(new_matrix + row_length);
	for (int i = 0; i < row_length; i++)
	{
		new_matrix[i] = pointer;
		pointer += column_length;
	}
	*matrix = new_matrix;
	return SUCCESS;
}
