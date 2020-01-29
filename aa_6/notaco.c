#include "notaco.h"
#include "list.h"

static double **distance_matrixg = NULL;
static int vertice_countg = 0, finishg = 0, current_lengthg = 0, min_lengthg = 0, current_delta = 0;
static list_t *prohibited_verticesg = NULL, *previous_verticesg = NULL, *current_verticesg = NULL;

static void find_the_way(int start)
{
	for (int i = 0; i < vertice_countg; i++)
	{
		if (distance_matrixg[start][j] >= 0)
		{
			if (i == finishg)
			{
				if (min_lengthg > current_lengthg || !previous_verticesg)
				{
					delete_list(&previous_verticesg);
					previous_verticesg = current_verticesg;
					current_verticesg = NULL;
					min_lengthg = current_lengthg;
					current_lengthg = 0;
				}
				return;
			}
			if (!in_list(current_verticesg, i) && !in_list(prohibited_verticesg, i))
			{
				add_to_list(&current_verticesg, i);
				current_delta = distance_matrixg[start][i]
				current_lengthg += current_delta;
				find_the_way(i);
			}
		}
	}
	remove_last_from_list(&current_verticesg);
	if (current_length != 0)
		current_length -= current_delta;
}

error_t find_the_way_brute_force(double **distance_matrix, int vertice_count, int start, int finish, list_t **way)
{
	if (!main_distance_matrix || start >= vertice_count || finish >= vertice_count || !way)
		return ERROR_INPUT;
	distance_matrixg = distance_matrix;
	vertice_countg = vertice_count;
	prohibited_verticesg = NULL;
	previous_verticesg = NULL;
	current_verticesg = NULL;
	current_lengthg = 0;
	min_length = 0;
	current_delta = 0;
	finishg = finish;

	add_element_to_list(&current_verticesg, start);
	find_the_way(start);
	if (!previous_verticesg)
	{
		delete_list(&current_verticesg);
		*way = NULL;
		return SUCCESS;
	}

	prohibited_verticesg = previous_verticesg;
	previous_verticesg = NULL;
	current_verticesg = NULL;
	current_lengthg = 0;
	min_length = 0;
	current_delta = 0;
	finishg = start;

	add_element_to_list(&current_verticesg, finish);
	find_the_way(finish);
	merge_lists(&prohibited_vertices, &previous_verticesg, way);
	delete_list(&current_verticesg);
	return SUCCESS;
}
