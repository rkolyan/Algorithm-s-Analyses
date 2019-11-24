#include <stdlib.h>
#include "func_forms.h"
#include "func_matrix_mult.h"
#include "io.h"

int main(void)
{
	int row1 = 0, col1 = 0, row2 = 0, col2 = 0, threads_count = 0;
	double *matrix1 = NULL, *matrix2 = NULL, *matrix_result = NULL;
	double *row_factor = NULL, *col_factor = NULL;
	thrd_t *threads = NULL;
	function_resourse_t *fr = NULL;
	
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

	write_count_of_threads(&threads_count);
	matrix_result = calloc(row1 * col2, sizeof(double));
	threads = malloc(sizeof(thrd_t) * threads_count);
	fr = malloc(sizeof(function_resourse_t) * threads_count);

	//3)Get result, using standard method multiplying
	standard_multiply_matrix(matrix1, matrix2, row1, col1, row2, col2, threads, threads_count, fr, matrix_result);
	print_matr(stdout, matrix_result, row1, col2);
	putchar('\n');
	for (int i = 0; i < row1 * col2; i++)
		matrix_result[i] = 0;
	
	row_factor = calloc(row1, sizeof(double));
	col_factor = calloc(col2, sizeof(double));

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
	free(threads);
	free(fr);
	return 0;
}
