#ifndef FUNC_MATRIX_MULT_H
#define FUNC_MATRIX_MULT_H

#include <threads.h>
#include "error_codes.h"

typedef struct
{
	int **matrix_result;
	int **matrix1;
	int **matrix2;
	int *row_factor;
	int *col_factor;
	int i1;
	int i2;
	int col_count1;
	int col_count2;
	int d;
} function_resourse_t;

error_t standard_multiply_matrix(int **matrix1, int **matrix2,
		int row_count1, int col_count1, int row_count2, int col_count2,
	       	thrd_t *threads, int threads_count, function_resourse_t *, int **matrix_result);

error_t vinograd_multiply_matrix(int **matrix1, int **matrix2, int *row_factor, int *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2,
	       	thrd_t *threads, int threads_count, function_resourse_t *, int **matrix_result);

#endif
