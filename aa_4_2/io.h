#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "error_codes.h"

error_t input_number(const char *word, int* number_pointer);
error_t input_numbers_in_matrix(int **matrix, int row, int col);
error_t print_matrix(FILE *f, int **matrix, int row, int col);

#endif
