#include "error_codes.h"

//Multiplying versions (Without optimizing)
//{

error_t standard_multiply_matrix(double *matrix1, double *matrix2, 
		int row_count1, int col_count1, int row_count2, int col_count2, double *matrix_result)
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
				sum += matrix1[i * col_count1 + k] * matrix2[k * col_count2 + j];
			matrix_result[i * col_count2 + j] = sum;
		}
	}
	return SUCCESS;
}

error_t vinograd_multiply_matrix(double *matrix1, double *matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, double *matrix_result)
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

//}

//Multiplying versions (optimized1)
//{

error_t standard_multiply_matrix_optimized(double *matrix1, double *matrix2, 
		int row_count1, int col_count1, int row_count2, int col_count2, double *matrix_result)
{
	if (!matrix1 || !matrix2 || !matrix_result || row_count1 <= 0 || col_count1 <= 0 || row_count2 <= 0 || col_count2 <= 0 || col_count1 != row_count2)
		return ERROR_INPUT;

	double sum = 0;
	int tmp_count1_length = 0, tmp_count2_length = 0;
	for (int i = 0; i < row_count1; i++)
	{
		for (int j = 0; j < col_count2; j++)
		{
			sum = 0;
			tmp_count2_length = 0;
			for (int k = 0; k < col_count1; k++)
			{
				sum += matrix1[tmp_count1_length + k] * matrix2[tmp_count2_length + j];
				tmp_count2_length += col_count2;
			}
			matrix_result[i * col_count2 + j] = sum;
		}
		tmp_count1_length += col_count1;
	}
	return SUCCESS;
}

error_t vinograd_multiply_matrix_optimized1(double *matrix1, double *matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, double *matrix_result)
{
	if (!matrix1 || !matrix2 || !matrix_result || !row_factor || !col_factor || row_count1 <= 0 || col_count1 <= 0 || row_count2 <= 0 || col_count2 <= 0 || col_count1 != row_count2)
		return ERROR_INPUT;

	for (int i = 0; i < row_count1; i++)
	{
		for (int j = 0; j < col_count1; j += 2)
			row_factor[i] += matrix1[i * col_count1 + j] * matrix1[i * col_count1 + j + 1];
	}
	for (int j = 0; j < col_count2; j++)
	{
		for (int i = 0; i < col_count1; i += 2)
			col_factor[j] += matrix2[i * col_count2 + j] * matrix2[(i + 1) * col_count2 + j];
	}
	for (int i = 0; i < row_count1; i++)
	{
		for (int j = 0; j < col_count2; j++)
		{
			matrix_result[i * col_count2 + j] = -row_factor[i] - col_factor[j];
			for (int k = 0; k < col_count1; k += 2)
				matrix_result[i * col_count2 + j] += (matrix1[i * col_count1 + k] + matrix2[(k + 1) * col_count2 + j]) * (matrix1[i * col_count1 + k + 1] + matrix2[(k * col_count2 + j)]);
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

error_t vinograd_multiply_matrix_optimized2(double *matrix1, double *matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, double *matrix_result)
{
	if (!matrix1 || !matrix2 || !matrix_result || !row_factor || !col_factor || row_count1 <= 0 || col_count1 <= 0 || row_count2 <= 0 || col_count2 <= 0 || col_count1 != row_count2)
		return ERROR_INPUT;

	int tmp_count1_length = 0, tmp_count2_length = 0;
	for (int i = 0; i < row_count1; i++)
	{
		for (int j = 0; j < col_count1; j += 2)
			row_factor[i] += matrix1[tmp_count1_length + j] * matrix1[tmp_count1_length + j + 1];
		tmp_count1_length += col_count1;
	}
	for (int j = 0; j < col_count2; j++)
	{
		tmp_count2_length = 0;
		for (int i = 0; i < col_count1; i += 2)
		{
			col_factor[j] += matrix2[tmp_count2_length + j] * matrix2[tmp_count2_length + col_count2 + j];
			tmp_count2_length += col_count2 << 1;
		}
	}
	tmp_count1_length = 0;
	tmp_count2_length = 0;
	for (int i = 0; i < row_count1; i++)
	{
		for (int j = 0; j < col_count2; j++)
		{
			matrix_result[tmp_count2_length + j] = -row_factor[i] - col_factor[j];
			for (int k = 0; k < col_count1; k += 2)
				matrix_result[tmp_count2_length + j] += (matrix1[tmp_count1_length + k] + matrix2[(k + 1) * col_count2 + j]) * (matrix1[tmp_count1_length + k + 1] + matrix2[(k * col_count2 + j)]);
		}
		tmp_count2_length += col_count2;
		tmp_count1_length += col_count1;
	}
	if (col_count1 & 1)
	{
		tmp_count1_length = col_count1;
		tmp_count2_length = 0;
		for (int i = 0; i < row_count1; i++)
		{
			for (int j = 0; j < col_count2; j++)
				matrix_result[tmp_count2_length + j] += matrix1[tmp_count1_length - 1] * matrix2[(row_count2 - 1) * col_count2 + j];
			tmp_count2_length += col_count2;
			tmp_count1_length += col_count1;
		}
	}

	return SUCCESS;
}
//}
