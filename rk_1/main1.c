#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "types_macroses.h"

int create_array_from_file(FILE *f, type_t **array)
{
	if (array == NULL || f == NULL)
		return ERROR;

	int kol;

	fscanf(f, "%d", &kol);
	*array = malloc(sizeof(type_t) * kol * kol);
	for (int i = 0; i < kol * kol; i++)
		fscanf(f, "%hhu", *array + i);
	return kol;
}

vertice_t1 **create_array_of_vertices(type_t *array, int kol)
{
	if (array == NULL || kol <= 0)
		return NULL;

	vertice_t1 **varray;
	int count = 0;

	varray = malloc(sizeof(vertice_t1 *) * kol);
	for (int i = 0; i < kol; i++)
		varray[i] = malloc(sizeof(vertice_t1));
	for (int i = 0; i < kol; i++, count = 0)
	{
		for (int j = 0; j < kol; j++)
		{
			if (i != j && (array[i * kol + j]))
				count++;
		}
		varray[i]->kol_of_vert = count;
		if (count != 0)
			varray[i]->array = malloc(sizeof(vertice_t1 *) * count);
		else
			varray[i]->array = NULL;
		varray[i]->num = i + 1;
		count = 0;
		for (int j = 0; j < kol; j++)
		{
			if (i != j && (array[i * kol + j]))
			{
				(varray[i]->array)[count] = varray[j];
				count++;
			}
		}
	}
	return varray;
}

void create_file(vertice_t1 **varray, int kol)
{
	FILE *f;
	f = fopen("res.dot", "w");
	fprintf(f, "digraph res\n{\n");
	for (int i = 0; i < kol; i++)
	{
		for (int j = 0; j < varray[i]->kol_of_vert; j++)
			fprintf(f, "\t%d -> %d;\n", i + 1, (varray[i]->array)[j]->num);
	}
	fprintf(f, "}\n");
	fclose(f);
}

int add_element_to_stack(stack_element_t **head, int num)
{
	if (head == NULL)
		return ERROR;
	
	stack_element_t *tmp;

	tmp = malloc(sizeof(stack_element_t));
	tmp->data = num;
	tmp->next = *head;
	*head = tmp;
	return SUCCESS;
}

void remove_stack(stack_element_t **head)
{
	if (head == NULL)
		return;

	stack_element_t *tmp;

	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

int is_num_in_stack(stack_element_t *head, int num)
{
	for (; head != NULL; head = head->next)
	{
		if (head->data == num)
			return 1;
	}
	return 0;
}

int fill_stack(vertice_t1 *vertice, stack_element_t **head)
{
	if (is_num_in_stack(*head, vertice->num))
		return SUCCESS;
	else
		add_element_to_stack(head, vertice->num);
	for (int i = 0; i < vertice->kol_of_vert; i++)
		fill_stack((vertice->array)[i], head);
	return SUCCESS;
}

void print_not_connected(stack_element_t **head, int kol, int num)
{
	printf("Вершины, недостижимые из %d:", num);
	for (int i = 1; i <= kol; i++)
	{
		if (!is_num_in_stack(*head, i))
			printf("%d ", i);
	}
	putchar('\n');
}

void destroy_graph(vertice_t1 **varray, int kol)
{
	for (int i = 0; i < kol; i++)
	{
		free(varray[i]->array);
		free(varray[i]);
	}
	free(varray);
}

int main(int argc, char **argv)
{
	type_t *array = NULL;
	FILE *f;
	int kol = 0;
	vertice_t1 **varray = NULL;
	stack_element_t *head = NULL;

	if (argc != 2)
		return ERROR;
	f = fopen(argv[1], "r");
	kol = create_array_from_file(f, &array);
	fclose(f);
	varray = create_array_of_vertices(array, kol);
	free(array);
	create_file(varray, kol);
	for (int i = 1; i <= kol; i++)
	{
		fill_stack(varray[i - 1], &head);
		print_not_connected(&head, kol, i);
		remove_stack(&head);
	}
	destroy_graph(varray, kol);
	system("dot -Tpng:gd res.dot > res.png");
	
	pid_t childpid = fork();
	if (childpid == 0)
		execl("/usr/bin/gthumb", "gthumb", "res.png");
	return SUCCESS;
}
