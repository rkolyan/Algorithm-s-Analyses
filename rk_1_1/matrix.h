#ifndef MATRIX_H
#define MATRIX_H

#include "boolean.h"
#include "error_codes.h"
#include "number_type.h"
#include <stdio.h>

error_t create_matrix_from_file(FILE *file, type_t **matrix, int *count);
boolean is_graph_is_not_oriented(type_t *matrix, int count);

#endif
