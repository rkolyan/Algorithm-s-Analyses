#ifndef FUNC_MATRIX_MULT_H
#define FUNC_MATRIX_MULT_H

#include <threads.h>
#include <time.h>
#include "error_codes.h"

typedef struct
{
	double **matrix_result;
	double **matrix1;
	double **matrix2;
	double *row_factor;
	double *col_factor;
	int i1;
	int i2;
	int j1;
	int j2;
	int col_count1;
	int col_count2;
	int row_count2;
	int d;
	clock_t begin;
	clock_t end;
} function_resourse_t;

void standard_multiply_matrix_thread(double **matrix1, double **matrix2,
		int row_count1, int col_count1, int row_count2, int col_count2,
	       	thrd_t *threads, int threads_count, function_resourse_t *, double **matrix_result, clock_t times[4]);

void vinograd_multiply_matrix_thread(double **matrix1, double **matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2,
	       	thrd_t *threads, int threads_count, function_resourse_t *, double **matrix_result, clock_t times[4]);

#endif
