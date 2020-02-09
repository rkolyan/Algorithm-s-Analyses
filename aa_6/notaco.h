#ifndef NOTACO_H
#define NOTACO_H

#include "error_codes.h"
#include "way.h"

error_t find_commivoyager_way_brute_force(double **distance_matrix, int vertices_count, way_t *result);

#endif
