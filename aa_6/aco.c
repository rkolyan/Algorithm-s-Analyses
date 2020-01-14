/* Муравьиный алгоритм для решения задачи коммивояжёра */

#include "aco.h"
#include <stdlib.h>
#include <math.h>
 
error_t initialize_way(way_t **way, int vertex_count)
{
	if (!way)
		return ERROR_INPUT;
	way_t *new_way = malloc(sizeof(way_t));
	new_way->itabu = 0;
	new_way->length = -1;
	new_way->tabu = malloc(sizeof(int) * vertex_count);
	*way = new_way;
	return SUCCESS;
}

error_t free_way(way_t **way)
{
	if (!way)
		return ERROR_INPUT;
	free((*way)->tabu);
	free(*way);
	*way = NULL;
	return SUCCESS;
}

error_t initialize_matrix(double ***matrix, int vertex_count)
{
	if (!matrix)
		return ERROR_INPUT;
	double **new_matrix = NULL;
	new_matrix = malloc((sizeof(double *) + sizeof(double) * vertex_count) * vertex_count);
	for (int i = 0; i < vertex_count; i++)
		new_matrix[i] = (double *)(new_matrix + vertex_count) + i * vertex_count;
	*matrix = new_matrix;
	return SUCCESS;
}

error_t free_matrix(double ***matrix)
{
	if (!matrix)
		return ERROR_INPUT;
	free(*matrix);
	*matrix = NULL;
	return SUCCESS;
}

error_t initialize_ants(way_t ***ants, int ant_count, int vertex_count, int start)
{
	if (!ants)
		return ERROR_INPUT;
	way_t **new_ants = NULL;
	new_ants = malloc(sizeof(way_t *) * ant_count);
	for (int i = 0; i < ant_count; i++)
	{
		new_ants[i] = malloc(sizeof(way_t));
		new_ants[i]->itabu = 1;
		new_ants[i]->length = 0.0;
		new_ants[i]->tabu = malloc(sizeof(int) * vertex_count);
		new_ants[i]->tabu[0] = start - 1;
	}
	*ants = new_ants;
	return SUCCESS;
}

error_t free_ants(way_t ***ants, int ant_count)
{
	if (!ants)
		return ERROR_INPUT;
	for (int i = 0; i < ant_count; i++)
	{
		free((*ants)[i]->tabu);
		free((*ants)[i]);
	}
	free(*ants);
	*ants = NULL;
	return SUCCESS;
}

// вероятность перехода муравья ant в вершину to
static double find_probability (int to, way_t *ant, double **pheromone_matrix, double **distance_matrix, int vertex_count)
{
	// если вершина уже посещена, возвращаем 0
	for (int i = 0; i < ant->itabu; ++i) 
		if (to == ant->tabu[i]) 
			return 0;
 
	double sum = 0.0;
	int from = ant->tabu[ant->itabu - 1];
	// считаем сумму в знаминателе
	for (int j = 0; j < vertex_count; ++j) 
	{
		int flag = 1;
		// проверяем, посещал ли муравей j вершину
		for (int i = 0; i < ant->itabu; ++i)
		   	if (j == ant->tabu[i])
			   	flag = 0;
		// если нет, тогда прибавляем к общей сумме
		if (flag)
		   	sum += pow(pheromone_matrix[from][j], ALPHA) * pow(distance_matrix[from][j], BETTA);
	}
	// возвращаем значение вероятности
	return pow(pheromone_matrix[from][to], ALPHA) * pow (distance_matrix[from][to], BETTA) / sum;
}
 
// основная функция алгоритма поиска
way_t *ant_colony_optimize(double **main_distance_matrix, double **distance_matrix, double **pheromone_matrix, 
						   way_t **ants, int ant_count, int vertex_count, int start, int finish, way_t *way)
{
	// инициализация данных о расстоянии и количестве феромона
	for (int i = 0; i < vertex_count; ++i) 
	{
		for (int j = 0; j < vertex_count; ++j)
		{
			pheromone_matrix[i][j] = 1.0 / vertex_count;
			if (i != j)
			   	distance_matrix[i][j] = 1.0 / main_distance_matrix[i][j];
		}
	}
 
	// основной цикл
	for (int t = 0; t < T_MAX; ++t)
   	{
		// цикл по муравьям
		for (int k = 0; k < ant_count; ++k)
	   	{
			// поиск маршрута для k-го муравья
			do 
			{
				int j_max = -1;
				double p_max = 0.0;
				for (int j = 0; j < vertex_count; j++) {
					// Проверка вероятности перехода в вершину j
					if (ants[k]->tabu[ants[k]->itabu - 1] != j)
				   	{
						double p = find_probability(j, ants[k], pheromone_matrix, distance_matrix, vertex_count);
						if (p && p >= p_max)
					   	{
							p_max = p;
							j_max = j;
						}
					}
				}
				ants[k]->length += main_distance_matrix[ants[k]->tabu[ants[k]->itabu - 1]][j_max];
				ants[k]->tabu[ants[k]->itabu++] = j_max;
			}
		   	while (ants[k]->tabu[ants[k]->itabu - 1] != finish);
			// оставляем феромон на пути муравья
			for (int i = 0; i < ants[k]->itabu - 1; ++i)
		   	{
				int from = ants[k]->tabu[i % ants[k]->itabu];
				int to = ants[k]->tabu[(i + 1) % ants[k]->itabu];
				pheromone_matrix[from][to] += Q / ants[k]->length;
				pheromone_matrix[to][from] = pheromone_matrix[from][to];
			}
			// проверка на лучшее решение
			if (ants[k]->length < way->length || way->length < 0)
		   	{
				way->itabu = ants[k]->itabu;
				way->length = ants[k]->length;
				for (int i = 0; i < way->itabu; ++i)
				   	way->tabu[i] = ants[k]->tabu[i];
			}
			// обновление муравьев
			ants[k]->itabu = 1;
			ants[k]->length = 0.0;
		}
		// цикл по ребрам
		for (int i = 0; i < vertex_count; ++i)
		{
			for (int j = 0; j < vertex_count; ++j)
			{
				// обновление феромона для ребра (i, j)
				if (i != j)
				   	pheromone_matrix[i][j] *= (1 - RHO);
			}
		}
	}
	// возвращаем кратчайший маршрут
	
	return SUCCESS;
}
