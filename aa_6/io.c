#include "io.h"
#include <stdlib.h>

error_t print_way(way_t *way)
{
	if (!way)
		return ERROR_INPUT;
	if (way->list)
	{
		printf("Самый короткий путь:%d", way->list->num + 1);
		list_t *current = way->list;
		do
		{
			current = current->next;
			printf("->%d", current->num + 1);
		}
		while (current != way->list);
		putchar('\n');
		printf("Длина самого короткого пути:%d", way->length);
		putchar('\n');
	}
	else
	{
		printf("В данном графе все пути тупиковые (нельзя найти гамильтонов путь)");
	}
	return SUCCESS;
}

error_t input_matrix_from_file(double ***matrix, int *count, FILE *file)
{
	if (!matrix || !file)
		return ERROR_INPUT;
	if (!fscanf(file, "%d", count))
		return ERROR_INCORRECT;
	*matrix = malloc(sizeof(double *) * (*count) + sizeof(double) * (*count) * (*count));
	for (int i = 0; i < (*count); i++)
		(*matrix)[i] = (double *)((*matrix) + (*count)) + i * (*count);

	for (int i = 0; i < (*count); i++)
	{
		for (int j = 0; j < (*count); j++)
		{
			if (!fscanf(file, "%lf", (*matrix)[i] + j))
			{
				free(matrix);
				return ERROR_INCORRECT;
			}
		}
	}

	return SUCCESS;
}

error_t input_integer(int *number, const char *name, char is_positive)
{
	if (!number || !name)
		return ERROR_INPUT;
	while (1)
	{
		printf("Введите %s (целое число):", name);
		if (scanf("%d", number) == 0)
		{
			puts("Вы ввели не целое число!");
			continue;
		}
		if (*number <= 0 && is_positive)
			puts("Вводимое число дожно быть положительным!");
		else
			break;
	}
	return SUCCESS;
}

error_t input_float(double *number, const char *name, char is_positive)
{
	if (!number || !name)
		return ERROR_INPUT;
	while (1)
	{
		printf("Введите %s (число):", name);
		if (scanf("%lf", number) == 0)
		{
			puts("Вы ввели не число!");
			continue;
		}
		if (*number <= 0 && is_positive)
			puts("Вводимое число дожно быть положительным!");
		else
			break;
	}
	return SUCCESS;
}

#define IS_POSITIVE 1
error_t input_parameters(parameters_t *parameters)
{
	if (!parameters)
		return ERROR_INPUT;
	input_float(&(parameters->alpha), "alpha", IS_POSITIVE);
	input_float(&(parameters->beta), "beta", IS_POSITIVE);
	input_float(&(parameters->Q), "Q", IS_POSITIVE);
	input_float(&(parameters->rho), "коэффициент испарения rho", IS_POSITIVE);
	input_integer(&(parameters->time), "время жизни колонии", 1);
	return SUCCESS;
}
