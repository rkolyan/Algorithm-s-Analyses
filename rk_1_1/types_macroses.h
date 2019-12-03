#ifndef _TYPES_MACR_FUNCS_H_
#define _TYPES_MACR_FUNCS_H_

typedef unsigned char type_t;

typedef struct stack_element
{
	int clique_size;
	int *clique;
	struct stack_element *next;
} stack_element_t;

typedef struct vertice
{
	int num;
	int vertice_count;
	int *numbers_array;
} vertice_t;

typedef struct stack_element2
{
	int num;
	struct stack_element2 *next;
} stack_element_t2;

#endif
