#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "func_memory.h"

int main(int argc, char **args)
{
	double **matrix = NULL;
	int count = atoi(args[1]);
	srand(time(NULL));
	initialize_matrix(&matrix, count);
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			matrix[i][j] = (double)( rand() % 100000000) / 10000;
			matrix[j][i] = matrix[i][j];
		}
	}

	FILE *file = fopen(args[2], "w");
	fprintf(file, "%d\n", count);
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
			fprintf(file, "%lf ", matrix[i][j]);
		fprintf(file, "\n");
	}
	fclose(file);
	free(matrix);
	return 0;
}
