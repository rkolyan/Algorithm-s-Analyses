#ifndef THREAD_RESOURCES_H
#define THREAD_RESOURCES_H

#include "automobile.h"
#include "error_codes.h"

#define MAX_ARRAY_LENGTH 100

typedef struct
{
    unsigned int object_counter;
    automobile_t **array;
} thread_resource_t;

error_t create_thread_resources_array(thread_resource_t **array, unsigned int length);
void free_thread_resources_array(thread_resource_t *array, unsigned int length);
error_t remove_from_queue(thread_resource_t *thread_resource, automobile_t **automobile);
error_t add_to_queue(thread_resource_t *thread_resource, automobile_t *automobile);
error_t free_all_automobiles(thread_resource_t *resource);

#endif
