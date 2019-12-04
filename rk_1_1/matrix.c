#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

error_t create_matrix_from_file(FILE *file, type_t **matrix, int *count)
{
	if (!matrix || !file || !count)
		return ERROR_INPUT;

	if (!fscanf(file, "%d", count))
		return ERROR_INCORRECT;
	int kol = (*count) * (*count);
	*matrix = malloc(sizeof(type_t) * kol);
	for (int i = 0; i < kol; i++)
	{
		if (!fscanf(file, "%hhu", *matrix + i))
			return ERROR_INCORRECT;
	}
	return SUCCESS;
}
