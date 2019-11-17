#include <stdio.h>

void print_matrix(unsigned int *matrix, int length1, int length2)
{
	for (int i = 0; i < length1; i++)
	{
		for (int j = 0; j < length2; j++)
			printf("%u ",matrix[i * length2 + j]);
		printf("\n");
	}
}
