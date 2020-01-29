#ifndef ANT_H
#define ANT_H

#include "list.h"

typedef struct
{
	int current_vertice;
	int path_length;
	list_t *prohibited_vertices;
} ant_t;

#endif 
