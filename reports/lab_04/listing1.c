#include "func_matrix_mult.h"

static int partly_standard_multiply_matrix(void *args)
{
	if(!args)
		return ERROR_INPUT;
	function_resourse_t *fr = args;
	int sum = 0;
	for (int i = fr->i1; i < fr->i2; i++)
	{
		for (int j = 0; j < fr->col_count2; j++)
		{
			sum = 0;
			for (int k = 0; k < fr->col_count1; k++)
				sum += (fr->matrix1)[i][k] * (fr->matrix2)[k][j];
			(fr->matrix_result)[i][j] = sum;
		}
	}
	return SUCCESS;
}

error_t standard_multiply_matrix(int **matrix1, int **matrix2, 
		int row_count1, int col_count1, int row_count2, int col_count2, 
		thrd_t *threads, int threads_count, function_resourse_t *fr, int **matrix_result)
{
	if (!matrix1 || !matrix2 || !matrix_result || row_count1 <= 0 || col_count1 <= 0 || row_count2 <= 0 || \
		       	col_count2 <= 0 || col_count1 != row_count2 || !threads || threads_count <= 0 || !fr)
		return ERROR_INPUT;
	int thread_row_count = row_count1 / threads_count;
	int thread_row_remainder = row_count1 % threads_count;
	for (int i = 0, c = 0; i < threads_count; i++)
	{
		(fr + i)->matrix_result = matrix_result;
		(fr + i)->matrix1 = matrix1;
		(fr + i)->col_count1 = col_count1;
		(fr + i)->matrix2 = matrix2;
		(fr + i)->col_count2 = col_count2;
		(fr + i)->i1 = c;
		if (thread_row_remainder)
		{
			c++;
			thread_row_remainder--;
		}
		c += thread_row_count;
		(fr + i)->i2 = c;
		thrd_create(threads + i, partly_standard_multiply_matrix, fr + i);
	}

	for (int i = 0; i < threads_count; i++)
		thrd_join(threads[i], NULL);

	return SUCCESS;
}
