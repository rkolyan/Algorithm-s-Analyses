#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <threads.h>
#include "function_resources.h"
#include "func_conveyer.h"
#include "func_thread_conveyer.h"
#include "memory_resources.h"

int main(void)
{
	int count2 = 0;
	double result = 0;
	struct timeval timer1, timer2;

	//printf("Введите кол-во элементов, которые будут обслуживаться контейнером:");
	//scanf("%d", &count1);
	printf("Введите кол-во итераций:");
	scanf("%d", &count2);

	memory_resource_t *all_resources = NULL;
	mtx_t *mutexes = NULL;
	cnd_t *conditional_variables = NULL;
	thrd_t *threads = NULL;
	function_resource_t *function_resources = NULL;
	automobile_t *automobile = NULL, **tmp = NULL; 
	
	create_memory_resources_array(&all_resources, THREADS_COUNT + 1);
	mutexes = calloc(THREADS_COUNT, sizeof(mtx_t));
	conditional_variables = calloc(THREADS_COUNT, sizeof(cnd_t));
	function_resources = calloc(THREADS_COUNT, sizeof (function_resource_t));
	threads = calloc(THREADS_COUNT, sizeof (thrd_t));
	fill_first_queue(all_resources);
	
	result = 0;
	for (int i = 0; i < count2; i++)
	{
		gettimeofday(&timer1, NULL);
		for (int i = 0; i < AUTOMOBILE_COUNT; i++)
		{
			remove_from_queue(all_resources, &automobile);
			create_body(automobile);
			add_to_queue(all_resources + 1, automobile);
			remove_from_queue(all_resources + 1, &automobile);
			create_circles(automobile);
			add_to_queue(all_resources + 2, automobile);
			remove_from_queue(all_resources + 2, &automobile);
			add_number(automobile);
			add_to_queue(all_resources + 3, automobile);
			remove_from_queue(all_resources + 3, &automobile);
			color_automobile(automobile);
			add_to_queue(all_resources + 4, automobile);
			remove_from_queue(all_resources + 4, &automobile);
			add_number(automobile);
			add_to_queue(all_resources + 5, automobile);
			automobile = NULL;
		}
		gettimeofday(&timer2, NULL);
		result += (double)(timer2.tv_sec - timer1.tv_sec) + (timer2.tv_usec - timer1.tv_usec) / 1000000.0;
	}

	printf("linear - %lf\n", result / count2);

	fill_function_resource(function_resources, all_resources, mutexes, conditional_variables, create_body, 1);
	fill_function_resource(function_resources + 1, all_resources + 1, mutexes, conditional_variables, create_circles, 0);
	fill_function_resource(function_resources + 2, all_resources + 2, mutexes + 1, conditional_variables + 1, add_number, 0);
	fill_function_resource(function_resources + 3, all_resources + 3, mutexes + 2, conditional_variables + 2, color_automobile, 0);
	fill_function_resource(function_resources + 4, all_resources + 4, mutexes + 3, conditional_variables + 3, add_number, 2);

	for (int i = 0; i < THREADS_COUNT - 1; i++)
	{
	    mtx_init(mutexes + i, mtx_plain | mtx_recursive);
		cnd_init(conditional_variables + i);
	}

	result = 0;

	for (int i = 0; i < count2; i++)
	{


		tmp = all_resources->array;
		all_resources->array = (all_resources + THREADS_COUNT)->array;
		all_resources->object_counter = AUTOMOBILE_COUNT;
		(all_resources + THREADS_COUNT)->array = tmp;
		(all_resources + THREADS_COUNT)->object_counter = 0;

		gettimeofday(&timer1, NULL);
		thrd_create(threads, begin_first_conveyer, function_resources);
		for (int i = 1; i < THREADS_COUNT - 1; i++)
			thrd_create(threads + i, begin_conveyer, function_resources + i);
		thrd_create(threads + THREADS_COUNT - 1, begin_last_conveyer, function_resources + THREADS_COUNT - 1);
		thrd_join(threads[THREADS_COUNT - 1], NULL);
		gettimeofday(&timer2, NULL);
		result += (double)(timer2.tv_sec - timer1.tv_sec) + (timer2.tv_usec - timer1.tv_usec) / 1000000.0;
	}

	printf("thread - %lf\n", result / count2);

	for (int i = 0; i < THREADS_COUNT - 1; i++)
	{
	    mtx_destroy(mutexes + i);
		cnd_destroy(conditional_variables + i);
	}

	return 0;
}
