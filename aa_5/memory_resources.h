#ifndef THREAD_RESOURCES_H
#define THREAD_RESOURCES_H

#include "automobile.h"
#include "error_codes.h"

#define MAX_ARRAY_LENGTH 20000

typedef struct
{
    unsigned int object_counter;
    automobile_t **array;
} memory_resource_t;

error_t create_memory_resources_array(memory_resource_t **array, unsigned int length);
void free_memory_resources_array(memory_resource_t *array, unsigned int length);
error_t remove_from_queue(memory_resource_t *memory_resource, automobile_t **automobile);
error_t add_to_queue(memory_resource_t *memory_resource, automobile_t *automobile);
char is_not_empty(memory_resource_t *element);
error_t fill_first_queue(memory_resource_t *memory_resource);

#endif
