#include "func_matrix_mult.h"
//Multiplying versions (Without optimizing)
//{

typedef struct
{
	double *row;
	double *col;
	int length;
	double *result;
} function_resourse_t;

static int multiply_row_on_col(void *args)
{
	function_resourse_t *fr = (function_resourse_t *)args;
	double sum = 0;
	for (int i = 0; i < fr->length; i++)
		sum += (fr->row)[i] * (fr->col)[i * (fr->length)];
	*(fr->result) = sum;
	return SUCCESS;
}

error_t standard_multiply_matrix(double *matrix1, double *matrix2, 
		int row_count1, int col_count1, int row_count2, int col_count2, 
		thrd_t *threads, int threads_count, double *matrix_result)
{
	if (!matrix1 || !matrix2 || !matrix_result || row_count1 <= 0 || col_count1 <= 0 || row_count2 <= 0 || \
		       	col_count2 <= 0 || col_count1 != row_count2 || !threads || threads_count <= 0)
		return ERROR_INPUT;
	function_resourse_t fr;
	int c = 0;
	for (int i = 0; i < row_count1; i++)
	{
		fr.row = matrix1 + i * col_count1;
		fr.length = col_count1;
		for (int j = 0; j < col_count2; j++)
		{
			fr.col = matrix2 + j;
			fr.result = matrix_result + i * col_count2 + j;
			thrd_create(threads + c, multiply_row_on_col, &fr);
			c++;
			if (c == threads_count)
				c = 0;
		}
	}
	return SUCCESS;
}

error_t vinograd_multiply_matrix(double *matrix1, double *matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, 
		thrd_t *threads, int threads_count, double *matrix_result)
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
