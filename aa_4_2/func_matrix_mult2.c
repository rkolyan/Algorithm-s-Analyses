void standard_multiply_matrix2(double **matrix1, double **matrix2, 
		int row_count1, int col_count1, int row_count2, int col_count2, double **matrix_result)
{
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
}

void vinograd_multiply_matrix2(double **matrix1, double **matrix2, double *row_factor, double *col_factor,
		int row_count1, int col_count1, int row_count2, int col_count2, double **matrix_result)
{
	int d = col_count1 >> 1;

	for (int i = 0; i < row_count1; i++)
	{
		for (int j = 0; j < col_count2; j++)
		{
			matrix_result[i][j] = -row_factor[i] - col_factor[j];
			for (int k = 0; k < d; k++)
				matrix_result[i][j] += (matrix1[i][k << 1] + matrix2[(k << 1) + 1][j]) * (matrix1[i][(k << 1) + 1] + matrix2[k << 1][j]);
		}
	}
	if (col_count1 & 1)
	{
		for (int i = 0; i < row_count1; i++)
		{
			for (int j = 0; j < col_count2; j++)
				matrix_result[i][j] += matrix1[i][col_count1 - 1] * matrix2[row_count2 - 1][j];
		}
	}
}
