#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <threads.h>

#include "func_matrix_creation.h"
#include "func_matrix_mult.h"

#define MATRIX_SIZE 1001
#define THREADS_COUNT 100
#define ITERATIONS_COUNT 10

int main(void)
{
	struct timeval timer1, timer2;
	int **matrix1 = NULL, **matrix2 = NULL, **matrix_result = NULL;
	thrd_t *threads = NULL;
	double result = 0;
	function_resourse_t *fr = NULL;
	create_matrix(MATRIX_SIZE, MATRIX_SIZE, &matrix1);
	create_matrix(MATRIX_SIZE, MATRIX_SIZE, &matrix2);
	create_matrix(MATRIX_SIZE, MATRIX_SIZE, &matrix_result);

	for (int t = 1; t <= THREADS_COUNT; t++)
	{
		fr = malloc(sizeof(function_resourse_t) * t);
		threads = malloc(sizeof(thrd_t) * t);
		result = 0;
		for (int j = 0; j < ITERATIONS_COUNT; j++)
		{
			fill_random_matrix_with_size(matrix1, MATRIX_SIZE, MATRIX_SIZE);
			fill_random_matrix_with_size(matrix2, MATRIX_SIZE, MATRIX_SIZE);
			fill_random_matrix_with_size(matrix_result, MATRIX_SIZE, MATRIX_SIZE);

			gettimeofday(&timer1, NULL);
			standard_multiply_matrix(matrix1, matrix2, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, threads, t, fr, matrix_result);
			gettimeofday(&timer2, NULL);
			result += (double)(timer2.tv_sec - timer1.tv_sec) + (timer2.tv_usec - timer1.tv_usec) / 1000000.0;
		}
		printf("%lf\n", result / ITERATIONS_COUNT);
		free(threads);
		free(fr);
	}
	puts("This is Vinograd");

	int *row_factor = NULL, *col_factor = NULL;
	for (int t = 1; t <= THREADS_COUNT; t++)
	{
		fr = malloc(sizeof(function_resourse_t) * t);
		threads = malloc(sizeof(thrd_t) * t);
		result = 0;
		for (int j = 0; j < ITERATIONS_COUNT; j++)
		{
			fill_random_matrix_with_size(matrix1, MATRIX_SIZE, MATRIX_SIZE);
			fill_random_matrix_with_size(matrix2, MATRIX_SIZE, MATRIX_SIZE);
			fill_random_matrix_with_size(matrix_result, MATRIX_SIZE, MATRIX_SIZE);
			create_vinograd_array(matrix1, MATRIX_SIZE, MATRIX_SIZE, 1, &row_factor);
			create_vinograd_array(matrix2, MATRIX_SIZE, MATRIX_SIZE, 0, &col_factor);

			gettimeofday(&timer1, NULL);
			vinograd_multiply_matrix(matrix1, matrix2, row_factor, col_factor, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, threads, t, fr, matrix_result);
			gettimeofday(&timer2, NULL);
			result += (double)(timer2.tv_sec - timer1.tv_sec) + (timer2.tv_usec - timer1.tv_usec) / 1000000.0;
			free(col_factor);
			free(row_factor);
		}
		printf("%lf\n", result / ITERATIONS_COUNT);
		free(threads);
		free(fr);
	}

	free(matrix1);
	free(matrix2);
	free(matrix_result);
	return 0;
}
