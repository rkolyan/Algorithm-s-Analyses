#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "parameters.h"
#include "way.h"

error_t print_way(way_t *way);
error_t input_matrix_from_file(double ***matrix, int *count, FILE *file);
error_t input_parameters(parameters_t *parameters);
error_t input_integer(int *number, const char *name, char is_positive);
error_t input_float(double *number, const char *name, char is_positive);

#endif
