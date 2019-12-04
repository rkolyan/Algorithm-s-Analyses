#ifndef CLIQUE_STACK_H
#define CLIQUE_STACK_H

#include "error_codes.h"
#include "number_type.h"
#include "vertices.h"

typedef struct clique_stack_element
{
	int clique_size;
	type_t *clique;
	struct clique_stack_element *next;
} clique_stack_element_t;

error_t add_clique_to_clique_stack(clique_stack_element_t **head, int count, type_t *clique);
error_t remove_clique_stack(clique_stack_element_t **head);

#endif
