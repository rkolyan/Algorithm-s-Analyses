#ifndef VERTICE_H
#define VERTICE_H

#include "error_codes.h"


typedef struct history_vertice
{
	int number;//TODO:?
	int vertice_count;
	struct history_vertice **next;
} history_vertice_t;

typedef struct graph_vertice
{
	int number;
	int vertice_count;
	int *next;
} graph_vertice_t;

error_t connect_graph_from_to(graph_vertice_t *vertice1, graph_vertice_t *vertice2);
error_t connect_history_from_to(history_vertice_t *vertice1, history_vertice_t *vertice2);

error_t create_dot_file(const char *filename, graph_vertice_t *graph, int count);

error_t initialize_graph(graph_vertice_t **graph, int vertice_count);
error_t free_graph(graph_vertice_t **graph, int vertice_count);

#endif
