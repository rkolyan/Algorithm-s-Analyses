#include <stdio.h>
#include <stdlib.h>
#include "func_conveyer.h"
#include "func_thread_conveyer.h"
#include "io.h"
#include "function_resources.h"
#include "memory_resources.h"
#include <time.h>

int main(void)
{
	memory_resource_t *all_resources = NULL;
	mtx_t *mutexes = NULL;
	cnd_t *conditional_variables = NULL;
	thrd_t *threads = NULL;
	function_resource_t *function_resources = NULL;
	
	create_memory_resources_array(&all_resources, THREADS_COUNT + 1);
	mutexes = calloc(THREADS_COUNT, sizeof(mtx_t));
	conditional_variables = calloc(THREADS_COUNT, sizeof(cnd_t));
	function_resources = calloc(THREADS_COUNT, sizeof (function_resource_t));
	threads = calloc(THREADS_COUNT, sizeof (thrd_t));
	fill_function_resource(function_resources, all_resources, mutexes, conditional_variables, create_body, 1);
	fill_function_resource(function_resources + 1, all_resources + 1, mutexes, conditional_variables, create_circles, 0);
	fill_function_resource(function_resources + 2, all_resources + 2, mutexes + 1, conditional_variables + 1, add_number, 0);
	fill_function_resource(function_resources + 3, all_resources + 3, mutexes + 2, conditional_variables + 2, color_automobile, 0);
	fill_function_resource(function_resources + 4, all_resources + 4, mutexes + 3, conditional_variables + 3, print_automobile, 2);
	fill_first_queue(all_resources);

	for (int i = 0; i < THREADS_COUNT - 1; i++)
	{
	    mtx_init(mutexes + i, mtx_plain | mtx_recursive);
		cnd_init(conditional_variables + i);
	}

	open_output();
	
	thrd_create(threads, begin_first_conveyer, function_resources);
	for (int i = 1; i < THREADS_COUNT - 1; i++)
	    thrd_create(threads + i, begin_conveyer, function_resources + i);
	thrd_create(threads + THREADS_COUNT - 1, begin_last_conveyer, function_resources + THREADS_COUNT - 1);
	thrd_join(threads[THREADS_COUNT - 1], NULL);

	close_output();

	for (int i = 0; i < THREADS_COUNT - 1; i++)
	{
	    mtx_destroy(mutexes + i);
		cnd_destroy(conditional_variables + i);
	}

	free(mutexes);
	free(conditional_variables);
	free_memory_resources_array(all_resources, THREADS_COUNT + 1);
	free(function_resources);
	free(threads);
	puts("Сгенерированные данные сохранены в файл result.txt");
	return 0;
}

