#include "list.h"
#include <stdio.h>
#include <stdlib.h>

error_t add_element_to_list(list_t **head, int num)
{
	if (!head)
		return ERROR_INPUT;
	if (!*head)
	{
		*head = malloc(sizeof(list_t));
		if (!*head)
			return ERROR_ALLOCATE;
		(*head)->next = *head;
		(*head)->previous = *head;
		(*head)->num = num;
	}
	else
	{
		list_t *element = malloc(sizeof(list_t));
		if (!element)
			return ERROR_ALLOCATE;
		element->previous = (*head)->previous;
		element->next = (*head);
		(*head)->previous->next = element;
		(*head)->previous = element;
		element->num = num;
	}
	return SUCCESS;
}

error_t delete_list(list_t **head)
{
	if (!head)
		return ERROR_INPUT;
	if (!*head)
		return SUCCESS;
	(*head)->previous->next = NULL;
	list_t *tmp = NULL;
	for (list_t *current = *head; current;)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*head = NULL;
	return SUCCESS;
}

void print_list(list_t *head)
{
	if (head)
	{
		printf("%d", head->num + 1);
		for (list_t *element = head->next; element != head; element = element->next)
			printf(", %d", element->num + 1);
		putchar('\n');
	}
	else
	{
		puts("0");
	}
}
