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
		printf("Введите %s: ", word);
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
			printf("%s должно быть > 0.\n", word);
		}
	}
}

//Function for correct input matrix parameters
void write_size_of_matrix(int *row)
{
	char *s = malloc(sizeof(char) * SBUF);
	test_string(s, "кол-во строк матрицы", row);
	free(s);
}

void write_first_and_last_vertice(int *vertex_number1, int *vertex_number2, int maximum)
{
	char *s = malloc(sizeof(char) * SBUF);
	do 
	{
		test_string(s, "номер начальной вершины", vertex_number1);
		if (*vertex_number1 > maximum)
			printf("Номер вершины должен быть меньше %d\n", maximum);
	}
	while (*vertex_number1 > maximum);
	*vertex_number2 = *vertex_number1;
	do 
	{
		test_string(s, "номер конечной вершины", vertex_number2);
		if (*vertex_number2 > maximum)
			printf("Номер вершины должен быть меньше %d!\n", maximum);
		else if (*vertex_number2 == *vertex_number1)
			printf("Номер конечной вершины не должен совпадать с номером начальной!\n");
	}
	while (*vertex_number2 > maximum || *vertex_number2 == *vertex_number1);
	free(s);
}

//Function for detecting errors in strings
error_t write_into_string(double *matr, int col)
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
void write_into_matrix(double **matrix, int row, int col)
{
	short fact;
	double *pointer = NULL;

	for (int i = 0; i < row; i++)
	{
		pointer = matrix[i];
		while (1)
		{
			printf("Введите числа в %d-ю строку:", i);
			fact = write_into_string(pointer, col);
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
	}
}

void print_way(way_t * way)
{
	printf("Длина пути: %d\n", way->length);
	printf("Путь: %d", way->tabu[0] + 1);
	for (int i = 1; i < way->itabu; ++i)
		printf(" -> %d", way->tabu[i] + 1);
	puts("");
}
