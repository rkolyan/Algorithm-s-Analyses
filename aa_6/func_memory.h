#ifndef FUNC_MEMORY_H
#define FUNC_MEMORY_H

#include "error_codes.h"
#include "way.h"

error_t initialize_matrix(double ***matrix, int vertex_count);
error_t free_matrix(double ***matrix);
error_t initialize_ants(way_t **ants, int ant_count);
error_t free_ants(way_t **ants, int ant_count);
error_t initialize_way(way_t **way);
error_t free_way(way_t **way);

#endif
