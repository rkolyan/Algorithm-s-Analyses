#include "boolean.h"
#include "clique_stack.h"
#include <stdio.h>
#include <stdlib.h>

//TODO: Change it
boolean is_clique_in_stack(clique_stack_element_t *head, type_t *clique, int clique_size)
{
	boolean flag1 = FALSE, flag2 = FALSE;
	for (; head != NULL; head = head->next)
	{
		flag1 = FALSE;
		if (head->clique_size != clique_size)
			continue;
		flag1 = TRUE;
		for (int i = 0; i < clique_size; i++)
		{
			flag2 = FALSE;
			for (int j = 0; j < head->clique_size; j++)
			{
				if (clique[i] == head->clique[j])
				{
					flag2 = TRUE;
					break;
				}
			}
			if (!flag2)
			{
				flag1 = FALSE;
				break;
			}
		}
		if (flag1)
			break;
	}
	return flag1;
}

error_t add_clique_to_clique_stack(clique_stack_element_t **head, int count, type_t *clique)
{
	if (!head)
		return ERROR_INPUT;
	
	clique_stack_element_t *tmp = NULL;

	tmp = malloc(sizeof(clique_stack_element_t));
	if (!tmp)
		return ERROR_ALLOCATE;
	tmp->clique_size = count;
	tmp->clique = clique;
	tmp->next = *head;
	*head = tmp;
	return SUCCESS;
}

error_t remove_clique_stack(clique_stack_element_t **head)
{
	if (!head)
		return ERROR_INPUT;

	clique_stack_element_t *tmp;

	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->clique);
		free(tmp);
	}
	return SUCCESS;
}

static boolean are_cliques_equalient(type_t *clique1, int count1, type_t *clique2, int count2)
{
	boolean flag = FALSE;
	for (int i = 0; i < count1; i++)
	{
		flag = FALSE;
		for (int j = 0; j < count2; j++)
		{
			if (clique1[i] == clique2[j])
			{
				flag = TRUE;
			}
		}
		if (!flag)
			return FALSE;
	}
	return TRUE;
}

error_t remove_duplicates_from_stack(clique_stack_element_t **head)
{
	if (!head)
		return ERROR_INPUT;
	clique_stack_element_t *previous = NULL;

	for (clique_stack_element_t *tmp = *head; tmp; tmp = tmp->next)
	{
		previous = tmp;
		for (clique_stack_element_t *tmp2 = tmp->next; tmp2; tmp2 = tmp2->next)
		{
			if (tmp->clique_size > tmp2->clique_size)
			{
				if (are_cliques_equalient(tmp2->clique, tmp2->clique_size, tmp->clique, tmp->clique_size))
				{
					previous->next = tmp2->next;
					free(tmp2->clique);
					free(tmp2);
					tmp2 = previous;
				}
			}
			else
			{
				if (are_cliques_equalient(tmp->clique, tmp->clique_size, tmp2->clique, tmp2->clique_size))
				{
					previous->next = tmp2->next;
					free(tmp2->clique);
					free(tmp2);
					tmp2 = previous;
				}
			}
			previous = previous->next;
		}
	}
	return SUCCESS;
}
