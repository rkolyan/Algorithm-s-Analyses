#include <stdio.h>

void print_matrix(unsigned int *matr, int row_count, int col_count, char *s1, char *s2)
{
	printf("%4c %4c ", ' ', '?');
	for (int j = 0; j < col_count; j++)
		printf("%4c ", s2[j]);
	printf("\n%4c ", '?');
	for (int j = 0; j < col_count + 1; j++)
		printf("%4u ", matr[j]);
	putchar('\n');
	for (int i = 0; i < row_count; i++)
	{
		printf("%4c ", s1[i]);
		for (int j = 0; j < col_count + 1; j++)
			printf("%4u ", matr[(i + 1) * (col_count + 1) + j]);
		putchar('\n');
	}
}
