/* Муравьиный алгоритм для решения задачи коммивояжёра */
#ifndef ACO_H
#define ACO_H

#include "error_codes.h"

#define N_MIN   3		   // минимальное количество вершин
#define N_MAX   30		  // максимальное количество вершин
 
#define ALPHA   1		   // вес фермента
#define BETTA   3		   // коэффициент эвристики
 
#define T_MAX   100		 // время жизни колонии
#define M	   20		  // количество муравьев в колонии
#define Q	   100		 // количество
#define RHO	 0.5		 // коэффициент испарения феромона
 
// структура ПУТЬ (длинна, массив вершин, количество вершин)
typedef struct
{
	int itabu;
	int length;
	int *tabu;
} way_t;

error_t initialize_way(way_t **way, int vertex_count);
error_t free_way(way_t **way);
error_t initialize_matrix(double ***matrix, int vertex_count);
error_t free_matrix(double ***matrix);
error_t initialize_ants(way_t ***ants, int ant_count, int vertex_count, int start);
error_t free_ants(way_t ***ants, int ant_count);
 
way_t *ant_colony_optimize(double **main_distance_matrix, double **distance_matrix, double **pheromone_matrix, 
						   way_t **ants, int ant_count, int vertex_count, int start, int finish, way_t *way);

#endif
