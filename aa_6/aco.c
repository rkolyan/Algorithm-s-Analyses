/* Муравьиный алгоритм для решения задачи коммивояжёра */

#include "aco.h"
#include <stdlib.h>
#include <math.h>
 
//Не изменять
static error_t fill_pheromones_and_attractions_default(double **pheromone_matrix, double **attraction_matrix, double **distance_matrix, int vertex_count)
{
	if (!pheromone_matrix || !attraction_matrix || !distance_matrix || !vertex_count)
		return ERROR_INPUT;
	for (int i = 0; i < vertex_count; ++i)
	{
		for (int j = 0; j < vertex_count; ++j)
		{
			pheromone_matrix[i][j] = 1.0 / vertex_count;
			if (i != j)
			   	attraction_matrix[i][j] = 1.0 / distance_matrix[i][j];
		}
	}
	return SUCCESS;
}

//Не изменять, не трогать!
static error_t update_pheromones(double **pheromone_matrix, int vertex_count, parameters_t *parameters)
{
	if (!pheromone_matrix || !vertex_count)
		return ERROR_INPUT;
	for (int i = 0; i < vertex_count; ++i)
	{
		for (int j = 0; j < vertex_count; ++j)
		{
			if (i != j)
				pheromone_matrix[i][j] *= (1 - parameters->rho);
		}
	}
	return SUCCESS;
}

static error_t choose_way_probably(double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, int previous, way_t *ant, parameters_t *parameters, int *result)
{
	if (!distance_matrix || !pheromone_matrix || !attraction_matrix || vertices_count <= 0 || !ant)
		return ERROR_INPUT;
	double sum1 = 0, sum2 = 0;
	double current_probability = ((double)(rand() % 10000)) / 10000;

	for (int i = 0; i < vertices_count; i++)
	{
		if (distance_matrix[previous][i] >= 0 && !in_list(ant->list, i))
			sum1 += pow(pheromone_matrix[previous][i], parameters->alpha) * pow(attraction_matrix[previous][i], parameters->beta);
	}

	for (int i = 0; i < vertices_count; i++)
	{
		if (distance_matrix[previous][i] >= 0 && !in_list(ant->list, i))
		{
			sum1 += pow(pheromone_matrix[previous][i], parameters->alpha) * pow(attraction_matrix[previous][i], parameters->beta);
			if (sum1 / sum2 >= current_probability)
			{
				*result = i;
				return SUCCESS;
			}
		}
	}
	*result = -1;
	return SUCCESS;
}

/*
error_t update_pheromones_for_path(double **pheromone_matrix, list_t *head, way_t *ant, parameters_t *parameters)
{
	if (!pheromone_matrix || !head || !ant || !parameters)
		return ERROR_INPUT;
	list_t *current = head;
	do
	{
		pheromone_matrix[current->num][current->next->num] = parameters->Q / ant->length;
		pheromone_matrix[current->next->num][current->num] = pheromone_matrix[current->num][current->next->num];
		current = current->next;
	}
	while (current->next != head);
	return SUCCESS;
}
*/

error_t find_commivoyager_way_aco(double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, way_t *ants, int ant_count, parameters_t *parameters, way_t *way)//По идее должен работать и для ориентированных графов
{
	if (!distance_matrix || !pheromone_matrix || !attraction_matrix || vertices_count <= 0 || !ants || ant_count <= 0)
		return ERROR_INPUT;
	fill_pheromones_and_attractions_default(pheromone_matrix, attraction_matrix, distance_matrix, vertices_count);
	for (int i = 0; i < parameters->time; i++)
	{
		//1)Установить муравьев в случайные города
		for (int j = 0; j < ant_count; j++)
		{
			//2)Сформировать маршрут для отдельного муравья
		}
		update_pheromones(pheromone_matrix, vertices_count, parameters);
	}
	return SUCCESS;
}
