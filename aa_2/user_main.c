#include <stdlib.h>
#include "func_forms.h"
#include "func_matrix_mult.h"
#include "func_matrix_creation.h"
#include "io.h"

int main(void)
{
	int row1 = 0, col1 = 0, row2 = 0, col2 = 0;
	double *matrix1 = NULL, *matrix2 = NULL, *matrix_result = NULL;
	double *row_factor = NULL, *col_factor = NULL;
	
	//1)Create matrix1
	write_size_of_matr(&row1, &col1);
	matrix1 = calloc(row1 * col1, sizeof(double));
	write_into_matr(matrix1, row1, col1);
	putchar('\n');
	print_matr(stdout, matrix1, row1, col1);
	putchar('\n');
	
	//2)Create matrix2
	write_size_of_matr(&row2, &col2);
	matrix2 = calloc(row2 * col2, sizeof(double));
	write_into_matr(matrix2, row2, col2);
	print_matr(stdout, matrix2, row2, col2);
	putchar('\n');

	matrix_result = calloc(row1 * col2, sizeof(double));

	//3)Get result, using standard method multiplying
	standard_multiply_matrix_optimized(matrix1, matrix2, row1, col1, row2, col2, matrix_result);
	print_matr(stdout, matrix_result, row1, col2);
	putchar('\n');
	for (int i = 0; i < row1 * col2; i++)
		matrix_result[i] = 0;
	
	create_vinograd_array(matrix1, row1, col1, 1, &row_factor);
	create_vinograd_array(matrix2, row2, col2, 0, &col_factor);
	//4)Get result, using vinograd method multiplying
	vinograd_multiply_matrix(matrix1, matrix2, row_factor, col_factor, row1, col1, row2, col2, matrix_result);
	print_matr(stdout, matrix_result, row1, col2);
	putchar('\n');
	
	//5)Free all memory and exit
	free(matrix1);
	free(matrix2);
	free(matrix_result);
	free(row_factor);
	free(col_factor);
	return 0;
}
