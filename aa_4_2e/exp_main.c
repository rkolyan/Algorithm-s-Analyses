#include <stdlib.h>
#include "func_matrix_creation.h"
#include "func_forms.h"
#include "func_matrix_mult.h"
#include "func_matrix_mult2.h"
#include "io.h"

int main(void)
{
	int threads_count = 0;
	double **matrix1 = NULL, **matrix2 = NULL, **matrix_result = NULL;
	double *row_factor = NULL, *col_factor = NULL;
	thrd_t *threads = NULL;
	function_resourse_t *fr = NULL;
	clock_t times[4] = {0};
	int some_num = 1;

	//Input thread_count
	threads = malloc(sizeof(thrd_t) * 64);
	fr = malloc(sizeof(function_resourse_t) * 64);
	for (int j = 1; j < 64; j <<= 2)
	{
		some_num = 1;
		for (int i = 100; i < 1002; i += some_num)
		{
			//1)Create matrix1
			create_matrix(i, i, &matrix1);
			create_matrix(i, i, &matrix2);
			create_matrix(i, i, &matrix_result);
			create_vinograd_array(matrix1, i, i, 1, &row_factor);
			create_vinograd_array(matrix2, i, i, 0, &col_factor);

			fill_random_matrix_with_size(matrix1, i, i);
			fill_random_matrix_with_size(matrix2, i, i);
			fill_random_matrix_with_size(matrix_result, i, i);

			//5)Get result, using standard method multiplying
			standard_multiply_matrix_thread(matrix1, matrix2, i, i, i, i, threads, threads_count, fr, matrix_result, times);
			fill_random_matrix_with_size(matrix_result, i, i);
			//TODO: Вычислить и вывести время

			times[0] = clock();
			standard_multiply_matrix(matrix1, matrix2, i, i, i, i, matrix_result);
			times[0] = clock() - times[0];
			//TODO: Вывести время
			fill_random_matrix_with_size(matrix_result, i, i);

			//6)Get result, using vinograd method multiplying
			vinograd_multiply_matrix_thread(matrix1, matrix2, row_factor, col_factor, i, i, i, i, threads, threads_count, fr, matrix_result, times);
			//TODO: Вычислить и вывести время
			fill_random_matrix_with_size(matrix_result, i, i);

			times[0] = clock();
			vinograd_multiply_matrix(matrix1, matrix2, row_factor, col_factor, i, i, i, i, matrix_result);
			times[0] = clock() - times[0];
			//TODO: Вывести время
			
			//7)Free all memory and exit
			free(matrix1);
			free(matrix2);
			free(matrix_result);
			free(row_factor);
			free(col_factor);
			if (some_num == 1)
				some_num = 99;
			else
				some_num = 1;
		}
	}
	free(threads);
	free(fr);
	return 0;
}
