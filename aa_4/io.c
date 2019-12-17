#include <stdio.h>
#include <stdlib.h>
#include "io.h"

static int test(char *s, int *num)
{
	int i = 0;
	while (s[i] != '-' && (s[i] < '0' || s[i] > '9'))
		i++;
	while (s[i] != '\0' && s[i] != '\n' && s[i] != ' ' && s[i] != '\t')
	{
		if (s[i] != '.' && (s[i] < '0' || s[i] > '9'))
			return 0;
		i++;
	}
	*num = atoi(s);
	return 1;
}

static void test_string(char *s, char *word, int* number)
{
	short err;
	while (1)
	{
		printf("Введите кол-во %s: ", word);
		fgets(s, SBUF, stdin);
		err = test(s, number);
		if (err && *number > 0)
		{
			break;
		}
		else if (err == 0)
		{
			printf("Вы ввели некорректное значение!\n");
		}
		else
		{
			printf("Кол-во %s должно быть > 0.\n", word);
		}
	}
}

//Function for correct input matrix parameters
void write_size_of_matr(int *row, int *col)
{
	char *s = malloc(sizeof(char) * SBUF);

	test_string(s, "строк матрицы", row);
	test_string(s, "столбцов матрицы", col);
	free(s);
}

void write_count_of_threads(int *threads_count)
{
	char *s = malloc(sizeof(char) * SBUF);
	test_string(s, "потоков", threads_count);
	free(s);
}

//Function for detecting errors in strings
error_t write_into_str(double *matr, int col)
{
	if (!matr || col <= 0)
		return ERROR_INPUT;

	char c = '\0';
	short fact_of_point = 0, fact_of_num = 0, fact_of_minus = 0;
	int k = 1;
	float num1 = 0, num2 = 0.1;
	double *tmp_matr = matr;

	do
	{
		c = getchar();

		if (c == '-' && !fact_of_minus)
		{
			k = -1;
			fact_of_minus = 1;
		}
		else if (c == '.' && !fact_of_point)
		{
			fact_of_point = 1;
			num2 = 0.1;
		}
		else if (c <= '9' && c >= '0' && fact_of_point)
		{
			num1 += num2 * (c - '0') * k;
			num2 *= 0.1;
			fact_of_num = 1;
		}
		else if (c <= '9' && c >= '0')
		{
			num1 = num1 * 10 + (c - '0') * k;
			fact_of_num = 1;
		}
		else if (c == ' ' || c == '\n' || c == EOF || c == '\t')
		{
			if (fact_of_num)
			{
				*tmp_matr = num1;
				tmp_matr++;
				num1 = 0;
				k = 1;
			}
			else if (!fact_of_num && (fact_of_point || fact_of_minus))
			{
				return ERROR_INCORRECT;
			}
			fact_of_num = 0;
			fact_of_point = 0;
			fact_of_minus = 0;
		}
		else 
			return ERROR_INCORRECT;
	}
	while (c != '\n' && c != EOF);
	
	if (tmp_matr != matr + col)
		return ERROR_NOT_IN_STRING;

	return SUCCESS;
}

//Function for input numbers into matrix
void write_into_matr(double *matr, int row, int col)
{
	short fact;

	for (int i = 0; i < row; i++)
	{
		while (1)
		{
			printf("Введите числа в %d-ю строку:", i);
			fact = write_into_str(matr, col);
			if (fact == SUCCESS)
			{
				break;
			}
			else if (fact == ERROR_NOT_IN_STRING)
			{
				printf("Кол-во введенных чисел не совпадает с нужным!\n");
			}
			else
			{
				printf("В это строке введены некорректные данные.\n");
			}
		}
		matr += col;
	}
}

//Beatiful print matrix
void print_matr(FILE *f, double *matr, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			fprintf(f, "%5.5f ", *(matr + i * col + j));
		fprintf(f, "\n");
	}
}
