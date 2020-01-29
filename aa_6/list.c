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

error_t remove_last_from_list(list_t **head)
{
	if (!head)
		return ERROR_INPUT;
	if (!*head)
		return SUCCESS;
	if ((*head)->next == *head)
	{
		free(*head);
		*head = NULL;
	}
	else
	{
		list_t *tmp = (*head)->previous;
		(*head)->previous = tmp->previous;
		tmp->previous->next = (*head);
		free(tmp);
	}
	return SUCCESS;
}

error_t merge_lists(list_t **head1, list_t **head2, list_t **head_result)
{
	if (!head1 || !head2 || !head_result)
		return ERROR_INPUT;
	if (!*head1)
	{
		*head_result = *head2;
	}
	else if (!*head2)
	{
		*head_result = *head1;
	}
	else
	{
		(*head1)->previous->next = (*head2);
		(*head2)->previous->next = (*head1);
		list_t *tmp = (*head2)->previous;
		(*head2)->previous = (*head1)->previous;
		(*head1)->previous = tmp;
		*head_result = (*head1);
	}
	*head1 = NULL;
	*head2 = NULL;
	return SUCCESS;
}

error_t copy_list(list_t *source, list_t **destination)
{
	if (!destination)
		return ERROR_INPUT;
	if (!source)
	{
		*destination = NULL;
	}
	else
	{
		list_t *current = source;
		do
		{
			add_element_to_list(destination, current->num);
			current = current->next;
		}
		while (current != source);
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

int in_list(list_t *head, int num)
{
	if (!head)
		return 0;
	list_t *current = head;
	do
	{
		if (current->num == num)
			return 1;
		current = current->next;
	}
	while (current != head);
	return 0;
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
