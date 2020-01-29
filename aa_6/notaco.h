#ifndef NOTACO_H
#define NOTACO_H

#include "error_codes.h"
#include "list.h"

error_t find_the_way_brute_force(double **main_distance_matrix, int start, int finish, list_t **way);

#endif
