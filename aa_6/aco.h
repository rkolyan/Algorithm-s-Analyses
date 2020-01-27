/* Муравьиный алгоритм для решения задачи коммивояжёра */
#ifndef ACO_H
#define ACO_H

#include "error_codes.h"
#include "way.h"

#define ALPHA   1		   // вес фермента
#define BETTA   3		   // коэффициент эвристики
 
#define T_MAX   100		 // время жизни колонии
#define M	   20		  // количество муравьев в колонии
#define Q	   100		 // количество
#define RHO	 0.5		 // коэффициент испарения феромона
 
error_t ant_colony_optimize(double **main_distance_matrix, double **distance_matrix, double **pheromone_matrix, 
						   way_t **ants, int ant_count, int vertex_count, int start, int finish, way_t *way);

#endif
