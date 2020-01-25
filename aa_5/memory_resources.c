#include "memory_resources.h"
#include <stdlib.h>

error_t create_memory_resources_array(memory_resource_t **array, unsigned int length)
{
	if (!array || !length)
		return ERROR_INPUT;
	*array = calloc(length, sizeof(memory_resource_t));
	if (!*array)
		return ERROR_ALLOCATE;
    for (unsigned int i = 0; i < length; i++)
	{
        (*array)[i].array = calloc(MAX_ARRAY_LENGTH, sizeof(automobile_t *));
		if (!(*array)[i].array)
		{
            for (unsigned int j = i; j >= 0; j--)
				free((*array)[i].array);
			free(*array);
			return ERROR_ALLOCATE;
		}
		(*array)[i].object_counter = 0;
	}
	return SUCCESS;
}

void free_memory_resources_array(memory_resource_t *resources, unsigned int length)
{
    for (unsigned int i = 0; i < length; i++)
	{
		for (unsigned int j = 0; j < resources[i].object_counter; j++)
			free((resources[i].array)[j]);
		free((resources)[i].array);
	}
	free(resources);
}

error_t remove_from_queue(memory_resource_t *memory_resource, automobile_t **result)
{
	if (!memory_resource || !result)
		return ERROR_INPUT;
	if (!memory_resource->object_counter)
		return SUCCESS;
	*result = memory_resource->array[0];
	for (unsigned int i = 1; i < memory_resource->object_counter; i++)
		memory_resource->array[i - 1] = memory_resource->array[i];
	memory_resource->object_counter--;
	memory_resource->array[memory_resource->object_counter] = NULL;
	return SUCCESS;
}

error_t add_to_queue(memory_resource_t *memory_resource, automobile_t *automobile)
{
	if (!memory_resource || !automobile)
		return ERROR_INPUT;
	if (!automobile)
		return SUCCESS;
    memory_resource->array[memory_resource->object_counter] = automobile;
    memory_resource->object_counter++;
	return SUCCESS;
}

error_t fill_first_queue(memory_resource_t *memory_resource)
{
	automobile_t *automobile = NULL;
	for (int i = 0; i < AUTOMOBILE_COUNT; i++)
	{
		automobile = malloc(sizeof(automobile_t));
		if (!automobile)
		{
			free_memory_resources_array(memory_resource, 1);
			return ERROR_ALLOCATE;
		}
		add_to_queue(memory_resource, automobile);
	}
	return SUCCESS;
}

char is_not_empty(memory_resource_t *element)
{
	if (element->object_counter)
		return 1;
	else
		return 0;
}
