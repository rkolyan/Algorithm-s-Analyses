#include <stdio.h>
#include <stdlib.h>
#include "io.h"

error_t input_number(const char *word, int* number_pointer)
{
	if (!word || !number_pointer)
		return ERROR_INPUT;
	short err = 0;
	while (1)
	{
		printf("Введите %s: ", word);
		err = scanf("%d", number_pointer);
		if (err && *number_pointer > 0)
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
	return SUCCESS;
}

//Function for detecting errors in strings
static error_t input_numbers_in_array(int *array, int col)
{
	if (!array || col <= 0)
		return ERROR_INPUT;
	short err = 0;
	char *buffer = calloc(col, 12);
	fgets(buffer, col * 12, stdin);
	for (int i = 0, current = 0; i < col && current < col * 12; i++)
	{
		while (buffer[current] == ' ' || buffer[current] == '\t')
			current++;
		if (buffer[current] == '\n' || buffer[current] == '\0')
		{
			printf("Количество введенных элементов - %d, должно быть - %d", i, col);
			return ERROR_NOT_IN_STRING;
		}
		err = sscanf(buffer + current, "%d", array + i);
		if (!err)
		{
			printf("Вы ввели некорректное значение в строке!");
			return ERROR_INCORRECT;
		}
		while (buffer[current] != ' ' && buffer[current] != '\t' && buffer[current] != '\n' && buffer[current] != '\0')
			current++;
	}
	return SUCCESS;
}

//Function for input numbers into matrix
error_t input_numbers_in_matrix(int **matrix, int row, int col)
{
	if (!matrix || row <= 0 || col <= 0)
		return ERROR_INPUT;
	error_t fact = SUCCESS;

	for (int i = 0; i < row; i++)
	{
		while (1)
		{
			printf("Введите числа в %d-ю строку:", i);
			fact = input_numbers_in_array(matrix[i], col);
			if (fact == SUCCESS)
				break;
		}
	}
	return SUCCESS;
}

//Beatiful print matrix
error_t print_matrix(FILE *file, int **matrix, int row, int col)
{
	if (!file || !matrix || row <= 0 || col <= 0)
		return ERROR_INPUT;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			fprintf(file, "%d\t", matrix[i][j]);
		fprintf(file, "\n");
	}
	return SUCCESS;
}
