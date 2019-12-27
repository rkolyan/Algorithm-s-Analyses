#include "thread_resources.h"
#include <stdlib.h>

error_t create_thread_resources_array(thread_resource_t **array, unsigned int length)
{
	if (!array || !length)
		return ERROR_INPUT;
	*array = calloc(length, sizeof(thread_resource_t));
	if (!*array)
		return ERROR_ALLOCATE;
    for (unsigned int i = 0; i < length; i++)
	{
        (*array + i)->array = calloc(MAX_ARRAY_LENGTH, sizeof(automobile_t *));
		if (!(*array + i)->array)
		{
            for (unsigned int j = i; j >= 0; j--)
				free((*array + i)->array);
			free(*array);
			return ERROR_ALLOCATE;
		}
	}
	return SUCCESS;
}

void free_thread_resources_array(thread_resource_t *array, unsigned int length)
{
    for (unsigned int i = 0; i < length; i++)
		free((array + i)->array);
	free(array);
}

error_t remove_from_queue(thread_resource_t *thread_resource, automobile_t **result)
{
	if (!thread_resource || !result)
		return ERROR_INPUT;
	if (!*result)
		return SUCCESS;
	*result = thread_resource->array[thread_resource->object_counter];
	for (unsigned int i = 1; i < thread_resource->object_counter; i++)
		thread_resource->array[i - 1] = thread_resource->array[i];
	thread_resource->object_counter--;
	return SUCCESS;
}

error_t add_to_queue(thread_resource_t *thread_resource, automobile_t *automobile)
{
	if (!thread_resource || !automobile)
		return ERROR_INPUT;
	if (!automobile)
		return SUCCESS;
    thread_resource->array[thread_resource->object_counter] = automobile;
    thread_resource->object_counter++;
	return SUCCESS;
}
