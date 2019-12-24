#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "error_codes.h"

//Function for correct input matrix parameters
void write_size_of_matr(int *row, int *col);
//Function for detecting errors in strings
error_t write_into_str(double *pointer, int count);
//Function for input numbers into matrix
void write_into_matr(double **matr, int row, int col);
//Beatiful print matrix
void print_matr(FILE *f, double **matr, int row, int col);

#define SBUF 150

#endif
