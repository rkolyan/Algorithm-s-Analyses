#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

#include "func_matrix_creation.h"
#include "func_matrix_mult.h"
#include "func_matrix_mult2.h"

#define MATRIX_SIZE 2000
#define THREADS_COUNT 8

int main(void)
{
	time_t timer;
	int **matrix1 = NULL, **matrix2 = NULL, **matrix_result = NULL;
	int *row_factor = NULL, *col_factor = NULL;
	thrd_t *threads = NULL;
	function_resourse_t *fr = NULL;
	create_matrix(MATRIX_SIZE, MATRIX_SIZE, &matrix1);
	fill_random_matrix_with_size(matrix1, MATRIX_SIZE, MATRIX_SIZE);
	create_matrix(MATRIX_SIZE, MATRIX_SIZE, &matrix2);
	fill_random_matrix_with_size(matrix2, MATRIX_SIZE, MATRIX_SIZE);
	create_matrix(MATRIX_SIZE, MATRIX_SIZE, &matrix_result);
	fill_random_matrix_with_size(matrix_result, MATRIX_SIZE, MATRIX_SIZE);
	fr = malloc(sizeof(function_resourse_t) * THREADS_COUNT);
	threads = malloc(sizeof(thrd_t) * THREADS_COUNT);

	timer = time(0);
	standard_multiply_matrix(matrix1, matrix2, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, threads, THREADS_COUNT, fr, matrix_result);
	printf("%lf\n", difftime(time(0), timer));
	fill_random_matrix_with_size(matrix1, MATRIX_SIZE, MATRIX_SIZE);
	fill_random_matrix_with_size(matrix2, MATRIX_SIZE, MATRIX_SIZE);
	fill_random_matrix_with_size(matrix_result, MATRIX_SIZE, MATRIX_SIZE);

	create_vinograd_array(matrix1, MATRIX_SIZE, MATRIX_SIZE, 1, &row_factor);
	create_vinograd_array(matrix2, MATRIX_SIZE, MATRIX_SIZE, 0, &col_factor);

	timer = time(0);
	vinograd_multiply_matrix(matrix1, matrix2, row_factor, col_factor, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, threads, THREADS_COUNT, fr, matrix_result);
	printf("%lf\n", difftime(time(0), timer));
	fill_random_matrix_with_size(matrix1, MATRIX_SIZE, MATRIX_SIZE);
	fill_random_matrix_with_size(matrix2, MATRIX_SIZE, MATRIX_SIZE);
	fill_random_matrix_with_size(matrix_result, MATRIX_SIZE, MATRIX_SIZE);

	timer = time(0);
	standard_multiply_matrix2(matrix1, matrix2, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, matrix_result);
	printf("%lf\n", difftime(time(0), timer));
	fill_random_matrix_with_size(matrix1, MATRIX_SIZE, MATRIX_SIZE);
	fill_random_matrix_with_size(matrix2, MATRIX_SIZE, MATRIX_SIZE);
	fill_random_matrix_with_size(matrix_result, MATRIX_SIZE, MATRIX_SIZE);

	timer = time(0);
	vinograd_multiply_matrix2(matrix1, matrix2, row_factor, col_factor, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, matrix_result);
	printf("%lf\n", difftime(time(0), timer));

	free(matrix1);
	free(matrix2);
	free(matrix_result);
	free(row_factor);
	free(col_factor);
	free(threads);
	free(fr);
	return 0;
}
