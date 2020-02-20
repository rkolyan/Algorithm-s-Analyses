error_t find_commivoyager_way_aco(double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, way_t *ants, int ant_count, parameters_t *parameters, way_t *result_way)
{
	if (!distance_matrix || !pheromone_matrix || !attraction_matrix || vertices_count <= 0 || !ants || ant_count <= 0)
		return ERROR_INPUT;
	fill_pheromones_and_attractions_default(pheromone_matrix, attraction_matrix, distance_matrix, vertices_count);
	for (int i = 0; i < parameters->time; i++)
	{
		set_ant_to_random_node(ants, ant_count, vertices_count);
		for (int j = 0; j < ant_count; j++)
		{
			build_path_for_ant(ants + j, distance_matrix, pheromone_matrix, attraction_matrix, vertices_count, parameters);
			if (is_way_shorter(ants, result_way))
			{
				clear_way(result_way);
				copy_way(ants + j, result_way);
			}
			update_pheromones_for_path(pheromone_matrix, ants + j, parameters);
			clear_way(ants + j);
		}
		update_pheromones(pheromone_matrix, vertices_count, parameters);
	}
	return SUCCESS;
}
