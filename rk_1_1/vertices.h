#ifndef VERTICES_H
#define VERTICES_H

#include "error_codes.h"
#include "number_type.h"

typedef struct vertice
{
	type_t num;
	int vertice_count;
	int *array;
} vertice_t;

error_t create_vertices(type_t *array, int count, vertice_t **varray);
error_t create_output_graph_file(vertice_t *varray, int count);
error_t remove_vertices(vertice_t **varray, int *count);

#endif
