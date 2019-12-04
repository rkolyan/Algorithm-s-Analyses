#ifndef CLIQUE_H
#define CLIQUE_H

#include "clique_stack.h"
#include "error_codes.h"
#include "vertices.h"

error_t find_cliques(vertice_t *varray, int count, clique_stack_element_t **head);
error_t print_cliques(vertice_t *varray, int count, clique_stack_element_t *head);

#endif
