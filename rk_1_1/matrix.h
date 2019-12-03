#ifndef MATRIX_H
#define MATRIX_H

#include "error_codes.h"
#include "number_type.h"
#include <stdio.h>

error_t create_matrix_from_file(FILE *file, type_t **matrix, int *count);

#endif
