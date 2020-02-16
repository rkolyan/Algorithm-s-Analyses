#include "vertice.h"
#include "error_codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

error_t create_dot_file(const char *filename, graph_vertice_t *graph, int count)
{
	if (!filename || !graph || count <= 0)
		return ERROR_INPUT;
	FILE *file = fopen(filename, "w");
	fputs("digraph\n", file);
	fputs("{\n", file);
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < graph[i].vertice_count; j++)
			fprintf(file, "%d -> %d\n", i + 1, graph[i].next[j] + 1);
	}
	fputs("}", file);
	fclose(file);
	return SUCCESS;
}

error_t connect_graph_from_to(graph_vertice_t *vertice1, graph_vertice_t *vertice2)
{
	if (!vertice1 || !vertice2)
		return ERROR_INPUT;
	if (vertice1->next)
	{
		void *tmp_pointer = malloc(sizeof(int) * (vertice1->vertice_count + 1));
		memcpy(tmp_pointer, vertice1->next, vertice1->vertice_count * sizeof(int));
		free(vertice1->next);
		vertice1->next = tmp_pointer;
		vertice1->next[vertice1->vertice_count] = vertice2->number;
		vertice1->vertice_count++;
	}
	else
	{
		vertice1->next = malloc(sizeof(int));
		vertice1->vertice_count = 1;
		vertice1->next[0] = vertice2->number;
	}
	return SUCCESS;
}

error_t initialize_graph(graph_vertice_t **graph, int vertice_count)
{
	if (!graph || vertice_count <= 0)
		return ERROR_INPUT;
	*graph = malloc(sizeof(graph_vertice_t) * vertice_count);
	if (!*graph)
		return ERROR_ALLOCATE;
	for (int i = 0; i < vertice_count; i++)
	{
		(*graph + i)->number = i;
		(*graph + i)->vertice_count = 0;
		(*graph + i)->next = NULL;
	}
	return SUCCESS;
}

error_t free_graph(graph_vertice_t **graph, int vertice_count)
{
	if (!graph || vertice_count <= 0)
		return ERROR_INPUT;
	for (int i = 0; i < vertice_count; i++)
	{
		if ((*graph)[i].next)
			free((*graph)[i].next);
	}
	free(*graph);
	*graph = NULL;
	return SUCCESS;
}

error_t connect_history_from_to(history_vertice_t *vertice1, history_vertice_t *vertice2)
{
	if (!vertice1 || !vertice2)
		return ERROR_INPUT;
	return SUCCESS;
}
