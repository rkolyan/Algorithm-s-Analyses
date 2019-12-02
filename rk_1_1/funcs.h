#ifndef FUNCS_H
#define FUNCS_H

#include "error_codes.h"
#include "types_macroses.h"

error_t create_array_from_file(FILE *file, type_t **array, int *count);
error_t create_array_of_vertices(type_t *array, int count, vertice_t **varray);
error_t create_file(vertice_t *varray, int count);
error_t fill_stack(vertice_t *vertice, stack_element_t **head);
error_t destroy_graph(vertice_t *varray, int *count);
//TODO: Add function for 

#endif
