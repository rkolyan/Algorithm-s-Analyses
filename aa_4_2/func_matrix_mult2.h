#ifndef FUNC_MATRIX_MULT2_H
#define FUNC_MATRIX_MULT2_H

void vinograd_multiply_matrix2(int **matrix1, int **matrix2, int *row_factor, int *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, int **matrix_result);
void standard_multiply_matrix2(int **matrix1, int **matrix2,
		int row_count1, int col_count1, int row_count2, int col_count2, int **matrix_result);

#endif
