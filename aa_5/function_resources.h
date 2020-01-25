#ifndef FUNCTION_RESOURCES_H
#define FUNCTION_RESOURCES_H

#include "error_codes.h"
#include "memory_resources.h"
#include <threads.h>

typedef struct
{
    error_t (*func)(automobile_t *);
    memory_resource_t *previous_queue;
    memory_resource_t *current_queue;
    mtx_t *previous_mutex;
    mtx_t *current_mutex;
	cnd_t *previous_cond;
	cnd_t *current_cond;
} function_resource_t;

void fill_function_resource(function_resource_t *function_resource, memory_resource_t *memory_resources,
		mtx_t *mutexes, cnd_t *conditional_variables, error_t (*func)(automobile_t *), char flag);

#endif
