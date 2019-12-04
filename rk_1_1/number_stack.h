#ifndef NUMBER_STACK_H
#define NUMBER_STACK_H

#include "error_codes.h"
#include "number_type.h"

typedef struct number_stack_element
{
	int num;
	struct number_stack_element *next;
} number_stack_element_t;

error_t add_number_to_number_stack(number_stack_element_t **head, type_t num);
void remove_number_stack(number_stack_element_t **head);

#endif
