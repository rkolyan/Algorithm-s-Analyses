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

static error_t update_pheromones(double **pheromone_matrix, int vertex_count)//TODO: Add parametrisation
{
	if (!pheromone_matrix || !vertex_count)
		return ERROR_INPUT;
	for (int i = 0; i < vertex_count; ++i)
	{
		for (int j = 0; j < vertex_count; ++j)
		{
			if (i != j)
				pheromone_matrix[i][j] *= (1 - RHO);
		}
	}
	return SUCCESS;
}

static error_t choose_way_probably(double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, ant_t *ant, int *result)
{
	if (!distance_matrix || !pheromone_matrix || !attraction_matrix || vertices_count <= 0 || !ant)
		return ERROR_INPUT;
	double sum1 = 0, sum2 = 0;
	double current_probability = ((double)(rand() % 10000)) / 10000;

	for (int i = 0; i < vertices_count; i++)
	{
		if (distance_matrix[ant->current_vertice][i] >= 0 && !in_list(ant->list))
			sum1 += pow(pheromone_matrix[ant->current_vertice][i], ALPHA) * pow(attraction_matrix[ant->current_vertice][i], BETTA);
	}

	for (int i = 0; i < vertices_count; i++)
	{
		if (distance_matrix[ant->current_vertice][i] >= 0 && !in_list(ant->list))
		{
			sum1 += pow(pheromone_matrix[ant->current_vertice][i], ALPHA) * pow(attraction_matrix[ant->current_vertice][i], BETTA);
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

error_t update_pheromones_for_path(double **pheromone_matrix, list_t *head, ant_t *ant)
{
	if (!pheromone_matrix || vertice_count <= 0 || !path)
		return ERROR_INPUT;
	list_t *current = head;
	do
	{
		pheromone_matrix[current->current_vertice][current->next->current_vertice] = Q / ant->length;
		pheromone_matrix[current->next->current_vertice][current->current_vertice] = pheromone_matrix[current->current_vertice][current->next->current_vertice];
	}
	while (current->next != head);
	return SUCCESS;
}

error_t clear_ant_info(ant_t *ant, int start_vertice)
{
	if (!ant || start_vertice < 0)
		return ERROR_INPUT;
	delete_list(&(ant->list));
	ant->current_vertice = start_vertice;
	ant->path_length = 0;
	return SUCCESS;
}

error_t find_the_way_aco(double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, ant_t *ants, int ant_count, int finish)//TODO: Add result variable, start variable
{
	if (!distance_matrix || !pheromone_matrix || !attraction_matrix || !vertices_count <= 0 || !ants || ant_count <= 0)
		return ERROR_INPUT;
	int next = -1;
	fill_pheromones_and_distances_default(pheromones_matrix, attraction_matrix, distance_matrix, vertices_count);
	for (int i = 0; i < T_MAX; i++)
	{
		for (int j = 0; j < ant_count; j++)
		{
			do
			{
				choose_way_probably(distance_matrix, pheromone_matrix, attraction_matrix, vertices_count, ant + j, &next);
				if (next != -1)
				{
					ant[j].length += distance_matrix[ant[j].current_vertice][next];
					add_element_to_list(&(ant[j].list), next);
					ant[j].current_vertice = next;
				}
			}
			while (next != -1 && next != finish);
			if (next != -1)
			{
				update_pheromones_for_path(pheromones_matrix, ant[j].list, ant);
				//TODO:if ant->length < min_length update way
			}
			clear_ant_info(ant + j, start);
		}
		update_pheromones(pheromone_matrix, int vertices_count);
	}
	return SUCCESS;
}
