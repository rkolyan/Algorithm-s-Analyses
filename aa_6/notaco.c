#include "func_memory.h"
#include "list.h"
#include "notaco.h"
#include "way.h"
#include <stdlib.h>

way_t *minimal_wayg = NULL, *current_wayg = NULL;
double **distance_matrixg = NULL;
int vertices_countg = 0, countg = 0;

static void find_the_wayg(int start)
{
	add_node_to_way(current_wayg, start);
	countg++;
	for (int i = 0; i < vertices_countg; i++)
	{
		if (i == start)
			continue;
		if (distance_matrixg[start][i] >= 0)
		{
			if (!in_way(current_wayg, i))
			{
				current_wayg->length += distance_matrixg[start][i];
				find_the_wayg(i);
				current_wayg->length -= distance_matrixg[start][i];
			}
		}
	}
	if (countg == vertices_countg && distance_matrixg[start][first_node_from_way(current_wayg)] >= 0)
	{
		current_wayg->length += distance_matrixg[start][first_node_from_way(current_wayg)];
		if (is_way_shorter(current_wayg, minimal_wayg))
		{
			clear_way(minimal_wayg);
			copy_way(current_wayg, minimal_wayg);
		}
		current_wayg->length -= distance_matrixg[start][first_node_from_way(current_wayg)];
	}
	remove_last_node_in_way(current_wayg);
	countg--;
}

error_t find_commivoyager_way_brute_force(double **distance_matrix, int vertices_count, way_t *result)
{
	if (!distance_matrix || !vertices_count || !result)
		return ERROR_INPUT;
	distance_matrixg = distance_matrix;
	vertices_countg = vertices_count;
	initialize_way(&minimal_wayg);
	initialize_way(&current_wayg);
	countg = 0;

	find_the_wayg(0);

	move_way(minimal_wayg, result);
	clear_way(minimal_wayg);
	free_way(&minimal_wayg);
	free_way(&current_wayg);
	vertices_countg = 0;
	distance_matrixg = NULL;
	return SUCCESS;
}
