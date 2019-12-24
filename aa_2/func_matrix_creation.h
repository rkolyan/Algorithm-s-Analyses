#ifndef FUNC_MATRIX_CREATION
#define FUNC_MATRIX_CREATION

#include "error_codes.h"

error_t create_vinograd_array(double *matrix, int row, int col, char method, double **array);

#endif
