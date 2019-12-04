#include "number_stack.h"
#include <stdlib.h>

error_t add_number_to_number_stack(number_stack_element_t **head, type_t num)
{
	if (!head)
		return ERROR_INPUT;
	
	number_stack_element_t *tmp = NULL;

	tmp = malloc(sizeof(number_stack_element_t));
	if (!tmp)
		return ERROR_ALLOCATE;
	tmp->num = num;
	tmp->next = *head;
	*head = tmp;
	return SUCCESS;
}

void remove_number_stack(number_stack_element_t **head)
{
	if (!head)
		return;
	number_stack_element_t *tmp = *head;
	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		free(tmp);
	}
}
