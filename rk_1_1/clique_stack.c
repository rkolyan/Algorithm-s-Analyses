#include <stdio.h>
#include <stdlib.h>
#include "clique_stack.h"

error_t add_clique_to_stack(stack_element_t **head, int count, int *clique)
{
	if (!head)
		return ERROR_INPUT;
	
	stack_element_t *tmp = NULL;

	tmp = malloc(sizeof(stack_element_t));
	if (!tmp)
		return ERROR_ALLOCATE;
	tmp->clique_size = count;
	tmp->clique = clique;
	tmp->next = *head;
	*head = tmp;
	return SUCCESS;
}

error_t remove_stack(stack_element_t **head)
{
	if (!head)
		return ERROR_INPUT;

	stack_element_t *tmp;

	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->clique);
		free(tmp);
	}
	return SUCCESS;
}

error_t fill_stack(vertice_t *vertice, stack_element_t **head)
{
	if (!vertice || !head)
		return ERROR_INPUT;
	else if (is_num_in_stack(*head, vertice->num))
		return SUCCESS;
	else
		add_element_to_stack(head, vertice->num);
	for (int i = 0; i < vertice->vertice_count; i++)
		fill_stack((vertice->array)[i], head);
	return SUCCESS;
}
