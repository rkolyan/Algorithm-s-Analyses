#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "error_codes.h"
#include "func_forms.h"
#include "func_analys.h"
#include "func_matrix_creation.h"

void find_calculations(int count1, int count2, int threads_count, function_t *functions, const char *filename)
{
	clock_t clocks = 0;
	FILE *file = NULL;
	double *matrix1 = NULL, *matrix2 = NULL, *matrix_result = NULL;
	thrd_t *threads = NULL;
	function_resourse_t *fr = NULL;

	srand(time(NULL));
	matrix1 = malloc(sizeof(double) * count1 * count1);
	matrix2 = malloc(sizeof(double) * count1 * count1);
	matrix_result = malloc(sizeof(double) * count1 * count1);
	threads = malloc(sizeof(thrd_t) * threads_count);
	fr = malloc(sizeof(function_resourse_t) * threads_count);
	file = fopen(filename, "w");
	for (int i = 1; i <= threads_count; i++)
	{
		for (int j = 0; j < count2; j++)
		{
			fill_random_matrix_with_size(count1, count1, matrix1);
			fill_random_matrix_with_size(count1, count1, matrix2);
			clocks += find_time(matrix1, matrix2, matrix_result, count1, count1, count1, threads, threads_count, fr, functions);
		}
		clocks /= count2;
		fprintf(file, "%ld\n", clocks);
	}
	fclose(file);
	free(threads);
	free(matrix1);
	free(matrix2);
	free(matrix_result);
	free(fr);
}

#define col1 row2
clock_t find_time(double *matr1, double *matr2, double *matr_res, int row1, int row2, int col2, thrd_t *threads, int threads_count, function_resourse_t *fr, function_t *functions)
{
	clock_t timer;
	//If it is standard
	if (functions->id == 0)
	{
		timer = clock();
		functions->standard_function(matr1, matr2, row1, col1, row2, col2, threads, threads_count, fr, matr_res);
		timer = clock() - timer;
	}
	else //If it is vinograd
	{
		double *row_factor = NULL, *col_factor = NULL;
		create_vinograd_array(matr1, row1, col1, 1, &row_factor);
		create_vinograd_array(matr2, row2, col2, 0, &col_factor);
		timer = clock();
		functions->vinograd_function(matr1, matr2, row_factor, col_factor, row1, col1, row2, col2, threads, threads_count, fr, matr_res);
		timer = clock() - timer;
		free(row_factor);
		free(col_factor);
	}
	return timer;
}

error_t fill_random_matrix_with_size(int row, int col, double *matrix)
{
	if (row <= 0 || col <= 0 || !matrix)
		return ERROR_INPUT;
	for (int i = 0, tmp_num = row * col; i < tmp_num; i++)
		matrix[i] = ((double)rand()) / 100000;
	return SUCCESS;
}
