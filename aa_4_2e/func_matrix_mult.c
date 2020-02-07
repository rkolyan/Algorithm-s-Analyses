#include "func_matrix_mult.h"
//Multiplying versions (Without optimizing)
//{

static int partly_standard_multiply_matrix(void *args)
{
	function_resourse_t *fr = (function_resourse_t *)args;
	fr->begin = clock();
	double sum = 0;
	if (fr->i2 > fr->i1)
	{
		for (int i = fr->i1; i < fr->i2; i++)
		{
			for (int j = fr->j1; j < fr->col_count2; j++)
			{
				sum = 0;
				for (int k = 0; k < fr->col_count1; k++)
					sum += fr->matrix1[i][k] * fr->matrix2[k][j];
				fr->matrix_result[i][j] = sum;
			}
			fr->j1 = 0;
		}
	}
	for (int j = fr->j1; j <= fr->j2; j++)
	{
		sum = 0;
		for (int k = 0; k < fr->col_count1; k++)
			sum += fr->matrix1[fr->i2][k] * fr->matrix2[k][j];
		fr->matrix_result[fr->i2][j] = sum;
	}
	fr->end = clock();
	return SUCCESS;
}

void standard_multiply_matrix_thread(double **matrix1, double **matrix2, 
		int row_count1, int col_count1, int row_count2, int col_count2, 
		thrd_t *threads, int threads_count, function_resourse_t *fr, double **matrix_result, clock_t times[4])
{
	times[0] = clock();
	int all = row_count1 * col_count2;
	int step = all / threads_count;
	int tmp = all % threads_count;
	int position = 0;
	times[1] = clock() - times[0];
	times[2] = 0;
	times[3] = clock();
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
		times[1] += clock() - times[3];
		times[3] = clock();
		thrd_create(threads + i, partly_standard_multiply_matrix, fr + i);
		times[2] += clock() - times[3];
	}
	for (int i = 0; i < threads_count; i++)
		thrd_join(threads[i], NULL);
	times[3] = clock();
}

static int partly_vinograd_multiply_matrix(void *args)
{
	function_resourse_t *fr = (function_resourse_t *)args;
	fr->begin = clock();
	double sum = 0;
	if (fr->i2 > fr->i1)
	{
		for (int i = fr->i1; i < fr->i2; i++)
		{
			for (int j = fr->j1; j < fr->col_count2; j++)
			{
				sum = -fr->row_factor[i] - fr->col_factor[j];
				for (int k = 0; k < fr->d; k++)
					sum += (fr->matrix1[i][k << 1] + fr->matrix2[(k << 1) + 1][j]) * (fr->matrix1[i][(k << 1) + 1] + fr->matrix2[k << 1][j]);
				if (fr->col_count1 & 1)
					sum += fr->matrix1[i][fr->col_count1 - 1] * fr->matrix2[fr->row_count2 - 1][j];
				fr->matrix_result[i][j] = sum;
			}
			fr->j1 = 0;
		}
	}
	for (int j = fr->j1; j <= fr->j2; j++)
	{
		sum = -fr->row_factor[fr->i2] - fr->col_factor[j];
		for (int k = 0; k < fr->d; k++)
			sum += (fr->matrix1[fr->i2][k << 1] + fr->matrix2[(k << 1) + 1][j]) * (fr->matrix1[fr->i2][(k << 1) + 1] + fr->matrix2[k << 1][j]);
		if (fr->col_count1 & 1)
			sum += fr->matrix1[fr->i2][fr->col_count1 - 1] * fr->matrix2[fr->row_count2 - 1][j];
		fr->matrix_result[fr->i2][j] = sum;
	}
	fr->end = clock();
	return SUCCESS;
}

void vinograd_multiply_matrix_thread(double **matrix1, double **matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, 
		thrd_t *threads, int threads_count, function_resourse_t *fr, double **matrix_result, clock_t times[4])
{
	times[0] = clock();
	int all = row_count1 * col_count2;
	int step = all / threads_count;
	int tmp = all % threads_count;
	int position = 0;
	int d = col_count1 >> 1;
	times[1] = clock() - times[0];
	times[2] = 0;
	times[3] = clock();
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
		(fr + i)->row_count2 = row_count2;
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
		times[1] += clock() - times[3];
		times[3] = clock();
		thrd_create(threads + i, partly_vinograd_multiply_matrix, fr + i);
		times[2] += clock() - times[3];
		times[3] = clock();
	}
	times[3] = clock();
	for (int i = 0; i < threads_count; i++)
		thrd_join(threads[i], NULL);
	times[2] += clock() - times[3];
	times[3] = clock();
}

