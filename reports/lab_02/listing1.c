#include "error_codes.h"

error_t standard_multiply_matrix(double **matrix1, double **matrix2, 
		int row_count1, int col_count1, int row_count2, int col_count2, double **matrix_result)
{
	if (!matrix1 || !matrix2 || !matrix_result || row_count1 <= 0 || col_count1 <= 0 || row_count2 <= 0 || col_count2 <= 0 || col_count1 != row_count2)
		return ERROR_INPUT;
	double sum = 0;
	for (int i = 0; i < row_count1; i++)
	{
		for (int j = 0; j < col_count2; j++)
		{
			sum = 0;
			for (int k = 0; k < col_count1; k++)
				sum += matrix1[i][k] * matrix2[k][j];
			matrix_result[i][j] = sum;
		}
	}
	return SUCCESS;
}

