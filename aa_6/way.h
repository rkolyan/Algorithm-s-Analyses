#ifndef WAY_H
#define WAY_H

#include "list.h"

typedef struct
{
	int length;
	list_t *list;
} way_t;

int first_node_from_way(way_t *way);
int in_way(way_t *way, int node_number);
int is_way_shorter(way_t *way1, way_t *way2);
error_t add_node_to_way(way_t *way, int node_number);
error_t remove_last_node_in_way(way_t *way);
error_t clear_way(way_t *way);
error_t move_way(way_t *source, way_t *destination);
error_t copy_way(way_t *source, way_t *destination);

#endif
