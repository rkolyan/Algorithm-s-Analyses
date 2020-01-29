/* Муравьиный алгоритм для решения задачи коммивояжёра */

#include "aco.h"
#include <stdlib.h>
#include <math.h>
 
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

static error_t update_pheromones(double **pheromone_matrix, int vertex_count, parameters_t *parameters)//TODO: Add parametrisation
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

error_t update_pheromones_for_path(double **pheromone_matrix, list_t *head, way_t *ant, parameters_t *parameters)
{
	if (!pheromone_matrix || !head || !ant || !parameters)
		return ERROR_INPUT;
	list_t *current = head;
	do
	{
		pheromone_matrix[current->num][current->next->num] = parameters->Q / ant->length;
		pheromone_matrix[current->next->num][current->num] = pheromone_matrix[current->num][current->next->num];
	}
	while (current->next != head);
	return SUCCESS;
}

error_t set_new_ant_info(way_t *ant, int start_vertice)
{
	if (!ant || start_vertice < 0)
		return ERROR_INPUT;
	delete_list(&(ant->list));
	ant->start_vertice = start_vertice;
	ant->length = 0;
	return SUCCESS;
}

error_t add_finish_start(way_t *current_way, double **distance_matrix, int *result)
{
	if (!current_way || !distance_matrix || !result)
		return ERROR_INPUT;
	if (distance_matrix[current_way->list->num][current_way->list->previous->num] >= 0)
	{
		current_way->length += distance_matrix[current_way->list->num][current_way->list->previous->num];
		*result = 1;
	}
	else
	{
		*result = -1;
	}
	return SUCCESS;
}

error_t find_commivoyager_way_aco(double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, way_t *ants, int ant_count, parameters_t *parameters, way_t *way)//По идее должен работать и для ориентированных графов
{
	if (!distance_matrix || !pheromone_matrix || !attraction_matrix || vertices_count <= 0 || !ants || ant_count <= 0)
		return ERROR_INPUT;
	int next = -1, previous = -1;
	int count = 0;
	fill_pheromones_and_attractions_default(pheromone_matrix, attraction_matrix, distance_matrix, vertices_count);
	for (int i = 0; i < parameters->time; i++)
	{
		for (int j = 0; j < ant_count; j++)
		{
			count = 0;
			set_new_ant_info(ants + j, rand() % vertices_count);
			previous = ants[j].start_vertice;
			do
			{
				choose_way_probably(distance_matrix, pheromone_matrix, attraction_matrix, vertices_count, previous, ants + j, parameters, &next);
				if (next != -1)
				{
					count++;
					ants[j].length += distance_matrix[previous][next];
					add_element_to_list(&(ants[j].list), next);
					previous = next;
				}
			}
			while (next != -1 && count < vertices_count - 1);
			if (next == -1)
				continue;
			add_finish_start(ants + j, distance_matrix, &next);
			if (next == -1)
			{
				set_new_ant_info(ants + j, 0);
				continue;
			}
			update_pheromones_for_path(pheromone_matrix, ants[j].list, ants, parameters);//TODO:Обновлять феромон, если муравей зашел в тупик, или нет?
			if (!(way->list) || way->length > ants[j].length)
			{
				delete_list(&(way->list));
				copy_list(ants[j].list, &(way->list));
				way->length = ants[j].length;
			}
			set_new_ant_info(ants + j, 0);
		}
		update_pheromones(pheromone_matrix, vertices_count, parameters);
	}
	return SUCCESS;
}
