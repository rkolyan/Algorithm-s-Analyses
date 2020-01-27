error_t initialize_way(way_t **way, int vertex_count)
{
	if (!way)
		return ERROR_INPUT;
	way_t *new_way = malloc(sizeof(way_t));
	new_way->tabu_count = 0;
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
		new_ants[i]->tabu_count = 1;
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
