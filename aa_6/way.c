#include "way.h"
#include "stddef.h"

int first_node_from_way(way_t *way)
{
	if (!way || !way->list)
		return -1;
	return way->list->num;
}

int in_way(way_t *way, int node_number)
{
	if (!way || node_number < 0)
		return 0;
	return in_list(way->list, node_number);
}

int is_way_shorter(way_t *way1, way_t *way2)
{
	if (!way1 || !way2 || !way1->list)
		return 0;
	if (!way2->list || way2->length > way1->length)
		return 1;
	return 0;
}

error_t add_node_to_way(way_t *way, int node_number)
{
	if (!way || node_number < 0)
		return ERROR_INPUT;
	add_element_to_list(&(way->list), node_number);
	return SUCCESS;
}

error_t remove_last_node_in_way(way_t *way)
{
	if (!way)
		return ERROR_INPUT;
	remove_last_from_list(&(way->list));
	return SUCCESS;
}

error_t clear_way(way_t *way)
{
	if (!way)
		return ERROR_INPUT;
	delete_list(&(way->list));
	way->length = 0;
	return SUCCESS;
}

error_t move_way(way_t *source, way_t *destination)
{
	if (!source || !destination)
		return ERROR_INPUT;
	destination->list = source->list;
	destination->length = source->length;
	source->list = NULL;
	return SUCCESS;
}

error_t copy_way(way_t *source, way_t *destination)
{
	if (!source || !destination)
		return ERROR_INPUT;
	copy_list(source->list, &destination->list);
	destination->length = source->length;
	return SUCCESS;
}
