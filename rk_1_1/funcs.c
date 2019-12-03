#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

error_t create_array_from_file(FILE *file, type_t **array, int *count)
{
	if (!array || !file || !count)
		return ERROR_INPUT;

	if (!fscanf(f, "%d", count));
		return ERROR_INCORRECT;
	int kol = (*count) * (*count);
	*array = malloc(sizeof(type_t) * kol);
	for (int i = 0; i < kol; i++)
	{
		if (!fscanf(f, "%hhu", *array + i))
			return ERROR_INCORRECT;
	}
	return SUCCESS;
}

error_t create_array_of_vertices(type_t *array, int count, vertice_t **varray)
{
	if (!array || !count || !varray)
		return ERROR_INPUT;

	int count1 = 0;
	vertice_t *tmp_varray = NULL;
	tmp_varray = malloc(sizeof(vertice_t) * count);
	if (!tmp_varray)
		return ERROR_ALLOCATE;
	for (int i = 0; i < count; i++, count1 = 0)
	{
		for (int j = 0; j < count; j++)
		{
			if (i != j && (array[i * count + j]))
				count1++;
		}
		tmp_varray[i]->vertice_count = count1;
		if (count1 != 0)
			(tmp_varray + i)->array = malloc(sizeof(int) * count1);
		else
			(tmp_varray + i)->array = NULL;
		tmp_varray[i]->num = i;
		count1 = 0;
		for (int j = 0; j < count; j++)
		{
			if (i != j && (array[i * count + j]))
			{
				((tmp_varray + i)->array)[count1] = j;
				count1++;
			}
		}
	}
	*varray = tmp_varray;
	return SUCCESS;
}

error_t create_file(vertice_t *varray, int count)
{
	if (!varray || !count)
		return ERROR_INPUT;

	FILE *file = fopen("res.dot", "w");
	fprintf(f, "digraph res\n{\n");
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < (varray + i)->vertice_count; j++)
			fprintf(f, "\t%d -> %d;\n", i + 1, ((varray + i)->array)[j]->num + 1);
	}
	fprintf(f, "}\n");
	fclose(f);

	return SUCCESS;
}

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

/*
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
*/

error_t remove_array_of_vertices(vertice_t **varray, int *count)
{
	if (!varray || !count)
		return ERROR_INPUT;

	for (int i = 0; i < *count; i++)
	{
		free((*varray + i)->array);
	}
	free(*varray);
	*varray = NULL;
	*count = 0;
	return SUCCESS;
}
