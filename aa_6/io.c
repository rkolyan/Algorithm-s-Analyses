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

error_t input_parameters(parameters_t *parameters)
{
	if (!parameters)
		return ERROR_INPUT;
	printf("Введите коэффициент alpha:");
	scanf("%lf", &(parameters->alpha));
	printf("Введите коэффициент beta:");
	scanf("%lf", &(parameters->beta));
	printf("Введите коэффициент Q:");
	scanf("%lf", &(parameters->Q));
	printf("Введите коэффициент испарения rho:");
	scanf("%lf", &(parameters->rho));
	printf("Введите время жизни колонии (кол-во циклов, целое число):");
	scanf("%d", &(parameters->time));
	return SUCCESS;
}
