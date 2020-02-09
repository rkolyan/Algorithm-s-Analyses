#include "func_memory.h"
#include <stdlib.h>

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

error_t initialize_ants(way_t **ants, int ant_count)
{
	if (!ants || ant_count <= 0)
		return ERROR_INPUT;
	way_t *new_ants = NULL;
	new_ants = malloc(sizeof(way_t) * ant_count);
	for (int i = 0; i < ant_count; i++)
	{
		new_ants[i].list = NULL;
		new_ants[i].length = 0;
	}
	*ants = new_ants;
	return SUCCESS;
}

error_t free_ants(way_t **ants, int ant_count)
{
	if (!ants)
		return ERROR_INPUT;
	for (int i = 0; i < ant_count; i++)
		delete_list(&((*ants)[i].list));
	free(*ants);
	*ants = NULL;
	return SUCCESS;
}

error_t initialize_way(way_t **way)
{
	if (!way)
		return ERROR_INPUT;
	*way = malloc(sizeof(way_t));
	(*way)->length = 0;
	(*way)->list = NULL;
	return SUCCESS;
}

error_t free_way(way_t **way)
{
	if (!way)
		return ERROR_INPUT;
	delete_list(&((*way)->list));
	free(*way);
	*way = NULL;
	return SUCCESS;
}
