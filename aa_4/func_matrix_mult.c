#include "func_matrix_mult.h"
//Multiplying versions (Without optimizing)
//{

static int partly_standard_multiply_matrix(void *args)
{
	if(!args)
		return ERROR_INPUT;
	function_resourse_t *fr = (function_resourse_t *)args;
	double sum = 0;
	if (fr->i2 > fr->i1)
	{
		for (int i = fr->i1; i < fr->i2; i++)
		{
			for (int j = fr->j1; j < fr->col_count2; j++)
			{
				sum = 0;
				for (int k = 0; k < fr->col_count1; k++)
					sum += fr->matrix1[i * fr->col_count1 + k] * fr->matrix2[k * fr->col_count2 + j];
				fr->matrix_result[i * fr->col_count2 + j] = sum;
			}
			fr->j1 = 0;
		}
	}
	for (int j = fr->j1; j <= fr->j2; j++)
	{
		sum = 0;
		for (int k = 0; k < fr->col_count1; k++)
			sum += fr->matrix1[fr->i2 * fr->col_count1 + k] * fr->matrix2[k * fr->col_count2 + j];
		fr->matrix_result[fr->i2 * fr->col_count2 + j] = sum;
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

	int all = row_count1 * col_count2;
	int step = all / threads_count;
	int tmp = all % threads_count;
	int position = 0;
	for (int i = 0; i < threads_count; i++)
	{
		(fr + i)->matrix1 = matrix1;
		(fr + i)->matrix2 = matrix2;
		(fr + i)->matrix_result = matrix_result;
		(fr + i)->col_count1 = col_count1;
		(fr + i)->col_count2 = col_count2;
		(fr + i)->i1 = position / col_count2;
		(fr + i)->j1 = position % col_count2;
		position += step - 1;
		if (tmp)
		{
			position++;
			tmp--;
		}
		(fr + i)->i2 = position / col_count2;
		(fr + i)->j2 = position % col_count2;
		position++;
		thrd_create(threads + i, partly_standard_multiply_matrix, fr + i);
	}
	for (int i = 0; i < threads_count; i++)
		thrd_join(threads[i], NULL);

	return SUCCESS;
}

static int partly_vinograd_multiply_matrix(void *args)
{
	if(!args)
		return ERROR_INPUT;
	function_resourse_t *fr = (function_resourse_t *)args;
	double sum = 0;
	if (fr->i2 > fr->i1)
	{
		for (int i = fr->i1; i < fr->i2; i++)
		{
			for (int j = fr->j1; j < fr->col_count2; j++)
			{
				sum = -fr->row_factor[i] - fr->col_factor[j];
				for (int k = 0; k < fr->d; k++)
					sum += (fr->matrix1[i * fr->col_count1 + (k << 1)] + fr->matrix2[((k << 1) + 1) * fr->col_count2 + j]) * (fr->matrix1[i * fr->col_count1 + (k << 1) + 1] + fr->matrix2[(k << 1) * fr->col_count2 + j]);
				if (fr->col_count1 & 1)
					sum += fr->matrix1[(i + 1) * fr->col_count1 - 1] * fr->matrix2[(fr->row_count - 1) * fr->col_count2 + j];
				fr->matrix_result[i * fr->col_count2 + j] = sum;
			}
			fr->j1 = 0;
		}
	}
	for (int j = fr->j1; j <= fr->j2; j++)
	{
		sum = -fr->row_factor[fr->i2] - fr->col_factor[j];
		for (int k = 0; k < fr->d; k++)
			sum += (fr->matrix1[fr->i2 * fr->col_count1 + (k << 1)] + fr->matrix2[((k << 1) + 1) * fr->col_count2 + j]) * (fr->matrix1[fr->i2 * fr->col_count1 + (k << 1) + 1] + fr->matrix2[(k << 1) * fr->col_count2 + j]);
		if (fr->col_count1 & 1)
			sum += fr->matrix1[(fr->i2 + 1) * fr->col_count1 - 1] * fr->matrix2[(fr->row_count - 1) * fr->col_count2 + j];
		fr->matrix_result[fr->i2 * fr->col_count2 + j] = sum;
	}
	return SUCCESS;
}

error_t vinograd_multiply_matrix(double *matrix1, double *matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, 
		thrd_t *threads, int threads_count, function_resourse_t *fr, double *matrix_result)
{
	if (!matrix1 || !matrix2 || !matrix_result || row_count1 <= 0 || col_count1 <= 0 || row_count2 <= 0 || \
		       	col_count2 <= 0 || col_count1 != row_count2 || !threads || threads_count <= 0 || !fr)
		return ERROR_INPUT;

	int all = row_count1 * col_count2;
	int step = all / threads_count;
	int tmp = all % threads_count;
	int position = 0;
	int d = col_count1 >> 1;
	for (int i = 0; i < threads_count; i++)
	{
		(fr + i)->matrix1 = matrix1;
		(fr + i)->matrix2 = matrix2;
		(fr + i)->matrix_result = matrix_result;
		(fr + i)->row_factor = row_factor;
		(fr + i)->col_factor = col_factor;
		(fr + i)->d = d;
		(fr + i)->col_count1 = col_count1;
		(fr + i)->col_count2 = col_count2;
		(fr + i)->row_count = row_count2;
		(fr + i)->i1 = position / col_count2;
		(fr + i)->j1 = position % col_count2;
		position += step - 1;
		if (tmp)
		{
			position++;
			tmp--;
		}
		(fr + i)->i2 = position / col_count2;
		(fr + i)->j2 = position % col_count2;
		position++;
		thrd_create(threads + i, partly_vinograd_multiply_matrix, fr + i);
	}
	for (int i = 0; i < threads_count; i++)
		thrd_join(threads[i], NULL);

	return SUCCESS;
}
