#ifndef VERTICES_H
#define VERTICES_H

#include "error_codes.h"

typedef struct vertice
{
	int num;
	int vertice_count;
	int *numbers_array;
} vertice_t;

error_t create_array_of_vertices(type_t *array, int count, vertice_t **varray);
error_t create_file_with_graph(vertice_t *varray, int count);
error_t remove_array_of_vertices(vertice_t **varray, int *count);

#endif
