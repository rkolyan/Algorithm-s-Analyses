#ifndef FUNC_MATRIX_MULT_H
#define FUNC_MATRIX_MULT_H

#include <threads.h>
#include "error_codes.h"

error_t vinograd_multiply_matrix(double *matrix1, double *matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2,
	       	thrd_t *threads, int threads_count, double *matrix_result);
error_t standard_multiply_matrix(double *matrix1, double *matrix2,
		int row_count1, int col_count1, int row_count2, int col_count2,
	       	thrd_t *threads, int threads_count, double *matrix_result);
/*
error_t vinograd_multiply_matrix_optimized1(double *matrix1, double *matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, double *matrix_result);
error_t vinograd_multiply_matrix_optimized2(double *matrix1, double *matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, double *matrix_result);
error_t standard_multiply_matrix_optimized(double *matrix1, double *matrix2,
		int row_count1, int col_count1, int row_count2, int col_count2, double *matrix_result);
*/
#endif
