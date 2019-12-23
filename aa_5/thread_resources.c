#include "thread_resources.h"
#include <stdlib.h>

error_t create_thread_resources_array(thread_resource_t **array, unsigned int length)
{
	if (!array || !length)
		return ERROR_INPUT;
	*array = calloc(length, sizeof(thread_resource_t));
	if (!*array)
		return ERROR_ALLOCATE;
	for (int i = 0; i < length; i++)
	{
		(*array + i)->array = calloc(MAX_ARRAY_LENGTH, sizeof(automobile_t));
		if (!(*array + i)->array)
		{
			for (int j = i; j >= 0; j--)
				free((*array + i)->array);
			free(*array);
			return ERROR_ALLOCATE;
		}
	}
	return SUCCESS;
}

void free_thread_resources_array(thread_resource_t *array, unsigned int length)
{
	for (int i = 0; i < length; i++)
		free((array + i)->array);
	free(array);
}
