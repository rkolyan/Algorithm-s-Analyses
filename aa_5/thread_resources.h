#ifndef THREAD_RESOURCES_H
#define THREAD_RESOURCES_H

#include "automobile.h"
#include "error_codes.h"

#define MAX_ARRAY_LENGTH 50

typedef struct
{
	int object_counter;
	automobile_t *array[MAX_ARRAY_LENGTH];
} thread_resource_t;

error_t create_thread_resources_array(thread_resource_t **array, unsigned int length);
void free_thread_resources_array(thread_resource_t *array, unsigned int length);

#endif
