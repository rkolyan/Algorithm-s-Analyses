#ifndef IO_H
#define IO_H

#include "aco.h"
#include "error_codes.h"

//Function for correct input matrix parameters
void write_size_of_matrix(int *row);
//Function for correct vertice parameters input
void write_first_and_last_vertice(int *vertex_number1, int *vertex_number2, int maximum);
//Function for detecting errors in strings
error_t write_into_string(double *pointer, int count);
//Function for input numbers into matrix
void write_into_matrix(double **matr, int row, int col);
//Beatiful print way
void print_way(way_t * way);

#define SBUF 150

#endif
