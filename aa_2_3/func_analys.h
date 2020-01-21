#ifndef FUNC_ANALYS_H
#define FUNC_ANALYS_H

#include <time.h>
#include "error_codes.h"
#include "func_forms.h"

void find_calculations(int count1, int count2, function_t *functions, const char *filename);
clock_t find_time(double **matrix1, double **matrix2, double **matrix_result, int row1, int row2, int col2, function_t *functions);
error_t fill_random_matrix_with_size(int row, int col, double **matrix);

#endif
