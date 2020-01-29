#ifndef ACO_H
#define ACO_H

#include "error_codes.h"
#include "parameters.h"
#include "way.h"

error_t find_commivoyager_way_aco(double **distance_matrix, double **pheromone_matrix, double **attraction_matrix, int vertices_count, way_t *ants, int ant_count, parameters_t *parameters, way_t *way);

#endif
