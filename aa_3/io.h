#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "error_codes.h"

#define SBUF 100

void write_size_of_array(int *count);
error_t write_into_str(double *array, int count);
void write_into_array(double *array, int count);
void print_array(FILE *f, double *array, int count);

#endif
