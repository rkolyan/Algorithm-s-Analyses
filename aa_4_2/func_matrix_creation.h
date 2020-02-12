#ifndef FUNC_MATRIX_CREATION
#define FUNC_MATRIX_CREATION

#include "error_codes.h"

error_t create_matrix(int row_length, int column_length, int ***matrix);
error_t create_vinograd_array(int **matrix, int row, int col, char method, int **array);
error_t fill_random_matrix_with_size(int **matrix, int row, int col);

#endif
