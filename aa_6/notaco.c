#include "notaco.h"

double **distance_matrixg = NULL;
int vertice_countg = 0, finishg = 0, current_lengthg = 0, min_lengthg = 0;
list_t *prohibited_verticesg = NULL, *previous_verticesg = NULL, *current_verticesg = NULL;
way_t *wayg = NULL;
char flagg = 0;

static void find_the_way(int start)
{
	for (int i = 0; i < vertice_countg; i++)
	{
		if (distance_matrixg[start][j] >= 0)
		{
			if (i == finishg)
			{
				if (min_lengthg > current_lengthg || !flag)
				{
					//delete_list(previous_verticesg)
					min_lengthg = current_lengthg
				}
				return;
			}
			if (not_in_list(current_verticesg, i) && not_in_list(prohibited_verticesg, i))
			{
				//TODO: Add to list number
				find_the_way(i);
			}
		}
	}
}

error_t find_the_way_brute_force(double **distance_matrix, int vertice_count, int start, int finish, way_t *way, list_t **prohibited_vertices)
{
	if (!main_distance_matrix || start >= vertice_count || finish >= vertice_count || !way || !prohibited_vertices)
		return ERROR_INPUT;
	distance_matrixg = distance_matrix;
	vertice_countg = vertice_count;
	prohibited_verticesg = prohibited_vertices;
	wayg = way;
	finishg = finish;

	return SUCCESS;
}
