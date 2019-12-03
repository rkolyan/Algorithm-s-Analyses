#include "clique.h"
#include "funcs.h"
#include <stdlib.h>

typedef char boolean;
#define TRUE 1
#define FALSE 0

//TODO: Change it
static boolean is_clique_in_stack(stack_element_t *head, int *clique, int clique_size)
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

static boolean is_vertice_is_part_of_clique(vertice_t *varray, int num, stack_element_t2 *head)
{
	if (!head)
		return FALSE;
	boolean flag = FALSE;
	while (!head)
	{
		flag = FALSE;
		for (int i = 0; i < (varray + head->num)->vertice_count; i++)
		{
			if ((varray + head->num)->array[i] == num)
			{
				flag = FALSE;
				break;
			}
		}
		if (!flag)
			return FALSE;
		head = head->next;
	}
	return TRUE;
}

static int *create_clique_from_number(stack_element_t2 *head)
{
	if (!head)
		return NULL;
	stack_element_t2 *tmp = head;
	int count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	if (!count)
		return NULL;
	int *array = calloc(count, sizeof(int));
	tmp = head;
	for (int i = count - 1; i > -1; i--)
	{
		array[i] = tmp->num;
		tmp = tmp->next;
	}
	return array;
}

void remove_number_stack(stack_element_t2 **head)
{
	if (!head)
		return;
	stack_element_t2 *tmp = *head;
	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		free(tmp);
	}
}

error_t find_cliques(vertice_t *varray, int count, stack_element_t **head)
{
	if (!varray || !count || !head)
		return ERROR_INPUT;
	int last_undetected = 0;
	int first_use = 0;
	int *clique = NULL;
	int clique_size = 0;
	boolean flag_undetected = FALSE;
	stack_element_t2 *stack = NULL;
	for (int i = 0; i < count; i++)
	{
		if (!(varray + i)->array)
			continue;
		first_use = 0;
		clique_size = 2;
		flag_undetected = TRUE;
		while (flag_undetected)
		{
			flag_undetected = FALSE;
			add_number_to_stack(&stack, (varray + i)->array[first_use]);
			for (int j = first_use + 1; j < (varray + i)->vertice_count; j++)
			{
				if (is_vertice_is_part_of_clique(varray, (varray + i)->array[j], stack))
				{
					add_number_to_stack(&stack, (varray + i)->array[j]);
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
			add_clique_to_stack(head, clique_size, clique);
			first_use = last_undetected;
		}
	}
	return SUCCESS;
}

//TODO: make it print_cliques
error_t print_not_connected(stack_element_t **head, int count, int num)
{
	if (!head || !count)
		return ERROR_INPUT;

	printf("Вершины, недостижимые из %d:", num);
	for (int i = 1; i <= count; i++)
	{
		if (!is_num_in_stack(*head, i))
			printf("%d ", i);
	}
	putchar('\n');
	return SUCCESS;
}
