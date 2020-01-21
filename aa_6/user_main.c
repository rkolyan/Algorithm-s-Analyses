/* Муравьиный алгоритм для решения задачи коммивояжёра */

#include "aco.h"
#include "io.h"
#include <stdlib.h>
#include <stdio.h>

int main (void) 
{
	way_t *way = NULL;
	way_t **ants = NULL;
	double **main_distance_matrix = NULL, **pheromone_matrix = NULL, **distance_matrix = NULL;
	int N = 0, A = 0, B = 0;
	
	// Инициализация матрицы расстояний
	write_size_of_matrix(&N);
	initialize_way(&way, N);
	initialize_matrix(&main_distance_matrix, N);
	write_into_matrix(main_distance_matrix, N, N);
	
	// Инициализация начальной и конечной точек
	write_first_and_last_vertice(&A, &B, N);

	// Инициализируем все необходимые для алгоритма ресурсы
	initialize_matrix(&pheromone_matrix, N);
	initialize_matrix(&distance_matrix, N);
	initialize_ants(&ants, M, N, A);

	// Запускаем алгоритм
	ant_colony_optimize(main_distance_matrix, distance_matrix, pheromone_matrix, ants, M, N, A - 1, B - 1, way);
	
	// Освобождаем все ненужные ресурсы
	free_ants(&ants, M);
	free_matrix(&distance_matrix);
	free_matrix(&pheromone_matrix);
	free_matrix(&main_distance_matrix);
 
	// Выводим результат (Длина пути и сам путь)
	print_way(way);

	// Освобождаем все оставшиеся ресурсы
	free_way(&way);

	return 0;
}
