#ifndef CLIQUE_STACK_H
#define CLIQUE_STACK_H

#include "error_codes.h"
#include "number_type.h"

typedef struct clique_stack_element
{
	int clique_size;
	type_t *clique;
	struct clique_stack_element *next;
} stack_element_t;

error_t add_clique_to_clique_stack(clique_stack_element_t **head, int count, int *clique);
error_t remove_clique_stack(clique_stack_element_t **head);
error_t fill_clique_stack(vertice_t *vertice, clique_stack_element_t **head);

#endif
