#include "function_resources.h"

void fill_function_resource(function_resource_t *function_resource, memory_resource_t *memory_resources,
		mtx_t *mutexes, cnd_t *conditional_variables, error_t (*func)(automobile_t *), char flag)
{
	function_resource->func = func;
	function_resource->previous_queue = memory_resources;
	function_resource->current_queue = memory_resources + 1;
	switch (flag)
	{
		case 1:
			function_resource->previous_mutex = NULL;
			function_resource->current_mutex = mutexes;
			function_resource->previous_cond = NULL;
			function_resource->current_cond = conditional_variables;
			break;
		case 2:
			function_resource->previous_mutex = mutexes;
			function_resource->current_mutex = NULL;
			function_resource->previous_cond = conditional_variables;
			function_resource->current_cond = NULL;
			break;
		default:
			function_resource->previous_mutex = mutexes;
			function_resource->current_mutex = mutexes + 1;
			function_resource->previous_cond = conditional_variables;
			function_resource->current_cond = conditional_variables + 1;
	}
}
