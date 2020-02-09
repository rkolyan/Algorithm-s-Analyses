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

error_t update_pheromones_for_path(double **pheromone_matrix, way_t *ant, parameters_t *parameters)//TODO: А что если путь = 0?
{
	if (!pheromone_matrix || !ant || !parameters)
		return ERROR_INPUT;
	if (!ant->list)
		return SUCCESS;
	list_t *current = ant->list;//Пахнет костылями
	do
	{
		pheromone_matrix[current->num][current->next->num] += parameters->Q / ant->length;
		pheromone_matrix[current->next->num][current->num] = pheromone_matrix[current->num][current->next->num];
		current = current->next;
	}
	while (current->next != ant->list);
	return SUCCESS;
}

error_t set_ant_to_random_node(way_t *ants, int ant_count, int vertice_count)
{
	if (!ants || ant_count <= 0 || vertice_count <= 0)
		return ERROR_INPUT;
	for (int i = 0; i < ant_count; i++)
	{
		clear_way(ants + i);
		add_node_to_way(ants + i, rand() % vertice_count);
	}
	return SUCCESS;
}

static error_t choose_next_node_probably(double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, int previous, way_t *ant, parameters_t *parameters, int *result)
{
	if (!distance_matrix || !pheromone_matrix || !attraction_matrix || vertices_count <= 0 || !ant)
		return ERROR_INPUT;
	double sum1 = 0, sum2 = 0;
	double current_probability = ((double)(rand() % 10000)) / 10000;

	for (int i = 0; i < vertices_count; i++)
	{
		if (distance_matrix[previous][i] >= 0 && !in_way(ant, i))
			sum2 += pow(pheromone_matrix[previous][i], parameters->alpha) * pow(attraction_matrix[previous][i], parameters->beta);
	}

	for (int i = 0; i < vertices_count; i++)
	{
		if (distance_matrix[previous][i] >= 0 && !in_way(ant, i))
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

error_t build_path_for_ant(way_t *ant, double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, parameters_t *parameters)
{
	if (!ant || !distance_matrix || !pheromone_matrix || !attraction_matrix || vertices_count <= 0 || !parameters)
		return ERROR_INPUT;
	int current = first_node_from_way(ant);
	int next = 0, count = 0;

	while (next != -1 && count != vertices_count - 1)
	{
		choose_next_node_probably(distance_matrix, pheromone_matrix, attraction_matrix, vertices_count, current, ant, parameters, &next);
		if (next == -1)
			break;
		ant->length += distance_matrix[current][next];
		add_node_to_way(ant, next);
		current = next;
		count++;
	}
	//TODO: Что, если зашел в тупик? Ладно, не будем усложнять жизнь
	ant->length += distance_matrix[current][first_node_from_way(ant)];

	return SUCCESS;
}

error_t find_commivoyager_way_aco(double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, way_t *ants, int ant_count, parameters_t *parameters, way_t *result_way)//Работает только для полных неориентированных графов
{
	if (!distance_matrix || !pheromone_matrix || !attraction_matrix || vertices_count <= 0 || !ants || ant_count <= 0)
		return ERROR_INPUT;
	fill_pheromones_and_attractions_default(pheromone_matrix, attraction_matrix, distance_matrix, vertices_count);
	for (int i = 0; i < parameters->time; i++)
	{
		//1)Установить муравьев в случайные города
		set_ant_to_random_node(ants, ant_count, vertices_count);
		for (int j = 0; j < ant_count; j++)
		{
			//2)Сформировать маршрут для отдельного муравья
			build_path_for_ant(ants + j, distance_matrix, pheromone_matrix, attraction_matrix, vertices_count, parameters);
			//3)Сравнить с кратчайшим, если меньше, то обновить путь
			if (is_way_shorter(ants, result_way))
			{
				clear_way(result_way);
				copy_way(ants + j, result_way);
			}
			//TODO: Нужно ещё проверить, не зашел ли муравей в тупик, и, в зависимости от этого решить, обновлять феромон или нет
			update_pheromones_for_path(pheromone_matrix, ants + j, parameters);
			clear_way(ants + j);
		}
		update_pheromones(pheromone_matrix, vertices_count, parameters);
	}
	return SUCCESS;
}
