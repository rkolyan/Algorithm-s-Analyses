#include "boolean.h"
#include "clique.h"
#include "clique_stack.h"
#include "number_stack.h"
#include "number_type.h"
#include <stdio.h>
#include <stdlib.h>

static boolean is_vertice_is_part_of_clique(vertice_t *varray, int num, number_stack_element_t *head)
{
	if (!head)
		return FALSE;
	boolean flag = FALSE;
	while (head)
	{
		flag = FALSE;
		for (int i = 0; i < (varray + head->num)->vertice_count; i++)
		{
			if ((varray + head->num)->array[i] == num)
			{
				flag = TRUE;
				break;
			}
		}
		if (!flag)
			return FALSE;
		head = head->next;
	}
	return TRUE;
}

static type_t *create_clique_from_number_stack(number_stack_element_t *head)
{
	if (!head)
		return NULL;
	number_stack_element_t *tmp = head;
	int count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	if (!count)
		return NULL;
	type_t *array = calloc(count, sizeof(type_t));
	tmp = head;
	for (int i = count - 1; i > -1; i--)
	{
		array[i] = tmp->num;
		tmp = tmp->next;
	}
	return array;
}

error_t find_cliques(vertice_t *varray, int count, clique_stack_element_t **head)
{
	if (!varray || !count || !head)
		return ERROR_INPUT;
	int last_undetected = 0;
	int first_use = 0;
	type_t *clique = NULL;
	int clique_size = 0;
	boolean flag_undetected = FALSE;
	number_stack_element_t *stack = NULL;
	for (int i = 0; i < count; i++)
	{
		if (!(varray + i)->array)
			continue;
		first_use = 0;
		flag_undetected = TRUE;
		while (flag_undetected)
		{
			flag_undetected = FALSE;
			clique_size = 2;
			add_number_to_number_stack(&stack, i);
			add_number_to_number_stack(&stack, (varray + i)->array[first_use]);
			for (int j = first_use + 1; j < (varray + i)->vertice_count; j++)
			{
				if (is_vertice_is_part_of_clique(varray, (varray + i)->array[j], stack))
				{
					add_number_to_number_stack(&stack, (varray + i)->array[j]);
					clique_size++;
				}
				else if (!flag_undetected)
				{
					last_undetected = j;
					flag_undetected = TRUE;
				}
			}
			clique = create_clique_from_number_stack(stack);
			remove_number_stack(&stack);
			add_clique_to_clique_stack(head, clique_size, clique);
			first_use = last_undetected;
		}
	}
	return SUCCESS;
}

error_t print_cliques(vertice_t *varray, int count, clique_stack_element_t *head)
{
	if (!varray)
	{
		puts("File reading error");
		return ERROR_INPUT;
	}
	puts("Cliques:");
	for (int i = 0; i < count; i++)
		printf("%d\n", i + 1);
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < (varray + i)->vertice_count; j++)
		{
			if ((varray + i)->array[j] > i)
				printf("%d %d\n", i + 1, (varray + i)->array[j] + 1);
		}
	}
	for (clique_stack_element_t *tmp = head; tmp; tmp = tmp->next)
	{
		for (int i = 0; i < tmp->clique_size; i++)
			printf("%d ", tmp->clique[i] + 1);
		puts("");
	}
	return SUCCESS;
}
