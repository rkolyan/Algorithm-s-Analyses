#ifndef FUNC_MATRIX_MULT2_H
#define FUNC_MATRIX_MULT2_H

void vinograd_multiply_matrix(double **matrix1, double **matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, double **matrix_result);
void standard_multiply_matrix(double **matrix1, double **matrix2,
		int row_count1, int col_count1, int row_count2, int col_count2, double **matrix_result);

#endif
