#include "func_matrix_mult.h"
//Multiplying versions (Without optimizing)
//{

static int partly_standard_multiply_matrix(void *args)
{
	function_resourse_t *fr = (function_resourse_t *)args;
	int j = fr->begin_position % fr->col_count2;
	int supj = fr->end_position - fr->begin_position + j;
	double sum = 0;
	for (int i = fr->begin_position / fr->col_count2, supi = fr->end_position / fr->col_count2 + 1; i < supi; i++)
	{
		for (; j < fr->col_count2 && j < supj; j++)
		{
			sum = 0;
			for (int k = 0; k < fr->col_count1; k++)
				sum += (fr->matrix1)[i * fr->col_count1 + k] * (fr->matrix2)[k * fr->col_count2 + j];
			(fr->matrix_result)[i * fr->col_count2 + j] = sum;
		}
		supj -= fr->col_count2;
		j = 0;
	}
	return SUCCESS;
}

error_t standard_multiply_matrix(double *matrix1, double *matrix2, 
		int row_count1, int col_count1, int row_count2, int col_count2, 
		thrd_t *threads, int threads_count, function_resourse_t *fr, double *matrix_result)
{
	if (!matrix1 || !matrix2 || !matrix_result || row_count1 <= 0 || col_count1 <= 0 || row_count2 <= 0 || \
		       	col_count2 <= 0 || col_count1 != row_count2 || !threads || threads_count <= 0 || !fr)
		return ERROR_INPUT;
	int tmp1 = row_count1 * col_count2;
	int tmp2 = tmp1 / threads_count;
	int position = 0;
	error_t error_code = SUCCESS;
	tmp1 = tmp1 % threads_count;
	for (int i = 0; i < threads_count; i++)
	{
		(fr + i)->matrix_result = matrix_result;
		(fr + i)->matrix1 = matrix1;
		(fr + i)->matrix2 = matrix2;
		(fr + i)->begin_position = position;
		position += tmp2;
		if (tmp1)
		{
			tmp1--;
			position++;
		}
		(fr + i)->end_position = position;
		(fr + i)->row_count = row_count1;
		(fr + i)->col_count1 = col_count1;
		(fr + i)->col_count2 = col_count2;
		thrd_create(threads + i, partly_standard_multiply_matrix, fr + i);
		thrd_join(threads[i], &error_code);
	}
	return error_code;
}

error_t vinograd_multiply_matrix(double *matrix1, double *matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, double *matrix_result)
{
	if (!matrix1 || !matrix2 || !matrix_result || !row_factor || !col_factor || row_count1 <= 0 || col_count1 <= 0 || row_count2 <= 0 || col_count2 <= 0 || col_count1 != row_count2)
		return ERROR_INPUT;

	int d = col_count1 / 2;
	for (int i = 0; i < row_count1; i++)
	{
		for (int j = 0; j < d; j++)
			row_factor[i] += matrix1[i * col_count1 + 2 * j] * matrix1[i * col_count1 + 2 * j + 1];
	}
	for (int j = 0; j < col_count2; j++)
	{
		for (int i = 0; i < d; i++)
			col_factor[j] += matrix2[(2 * i) * col_count2 + j] * matrix2[(2 * i + 1) * col_count2 + j];
	}
	for (int i = 0; i < row_count1; i++)
	{
		for (int j = 0; j < col_count2; j++)
		{
			matrix_result[i * col_count2 + j] = -row_factor[i] - col_factor[j];
			for (int k = 0; k < d; k++)
				matrix_result[i * col_count2 + j] += (matrix1[i * col_count1 + 2 * k] + matrix2[(2 * k + 1) * col_count2 + j]) * (matrix1[i * col_count1 + 2 * k + 1] + matrix2[(2 * k * col_count2 + j)]);
		}
	}
	if (col_count1 & 1)
	{
		for (int i = 0; i < row_count1; i++)
		{
			for (int j = 0; j < col_count2; j++)
				matrix_result[i * col_count2 + j] += matrix1[(i + 1) * col_count1 - 1] * matrix2[(row_count2 - 1) * col_count2 + j];
		}
	}

	return SUCCESS;
}
