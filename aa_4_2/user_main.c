#include <stdlib.h>
#include "func_matrix_creation.h"
#include "func_matrix_mult.h"
#include "io.h"

int main(void)
{
	int row1 = 0, col1 = 0, row2 = 0, col2 = 0, threads_count = 0;
	int **matrix1 = NULL, **matrix2 = NULL, **matrix_result = NULL;
	int *row_factor = NULL, *col_factor = NULL;
	thrd_t *threads = NULL;
	function_resourse_t *fr = NULL;
	
	input_number("количество строк 1-й матрицы", &row1);
	input_number("количество столбцов 1-й матрицы", &col1);
	getchar();//Почему-то поток ввода ведет себя неадекватно, поэтому это нужно

	create_matrix(row1, col1, &matrix1);
	input_numbers_in_matrix(matrix1, row1, col1);
	putchar('\n');
	print_matrix(stdout, matrix1, row1, col1);
	putchar('\n');
	
	input_number("количество строк 2-й матрицы", &row2);
	input_number("количество столбцов 2-й матрицы", &col2);
	getchar();//Почему-то поток ввода ведет себя неадекватно, поэтому это нужно

	create_matrix(row2, col2, &matrix2);
	input_numbers_in_matrix(matrix2, row2, col2);
	putchar('\n');
	print_matrix(stdout, matrix2, row2, col2);
	putchar('\n');

	create_matrix(row1, col2, &matrix_result);
	input_number("количество потоков", &threads_count);
	threads = malloc(sizeof(thrd_t) * threads_count);
	fr = malloc(sizeof(function_resourse_t) * threads_count);

	standard_multiply_matrix(matrix1, matrix2, row1, col1, row2, col2, threads, threads_count, fr, matrix_result);
	print_matrix(stdout, matrix_result, row1, col2);
	putchar('\n');
	
	create_vinograd_array(matrix1, row1, col1, 1, &row_factor);
	create_vinograd_array(matrix2, row2, col2, 0, &col_factor);

	vinograd_multiply_matrix(matrix1, matrix2, row_factor, col_factor, row1, col1, row2, col2, threads, threads_count, fr, matrix_result);
	print_matrix(stdout, matrix_result, row1, col2);
	putchar('\n');
	
	free(matrix1);
	free(matrix2);
	free(matrix_result);
	free(row_factor);
	free(col_factor);
	free(threads);
	free(fr);
	return 0;
}
