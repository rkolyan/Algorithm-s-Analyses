#include "func_thread_conveyer.h"
#include "io.h"
#include <stdlib.h>
#include <time.h>

error_t begin_first_conveyer(void *function_resourse)
{
	function_resourse_t *fr = function_resourse;
	if (!fr->func || !fr->previous_queue || !fr->current_queue || !fr->current_mutex)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
	srand(time(NULL));
	while(fr->previous_queue->object_counter)
	{
		remove_from_queue(fr->previous_queue, &automobile);
		fr->func(automobile);
		mtx_lock(fr->current_mutex);
		add_to_queue(fr->current_queue, automobile);
		mtx_unlock(fr->current_mutex);
		fr->previous_queue->object_counter--;
	}
	return SUCCESS;
}

error_t begin_conveyer(void *function_resourse)
{
	function_resourse_t *fr = function_resourse;
	if (!fr->func || !fr->previous_queue || !fr->current_queue || !fr->previous_mutex || !fr->current_mutex)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
	srand(time(NULL));
	while(1)
	{
		mtx_lock(fr->previous_mutex);
		remove_from_queue(fr->previous_queue, &automobile);
		mtx_unlock(fr->previous_mutex);
		fr->func(automobile);
		mtx_lock(fr->current_mutex);
		add_to_queue(fr->current_queue, automobile);
		mtx_unlock(fr->current_mutex);
		automobile = NULL;
	}
	return SUCCESS;
}

error_t begin_last_conveyer(void *function_resourse)
{
	function_resourse_t *fr = function_resourse;
    if (!fr->func || !fr->previous_queue || !fr->previous_mutex)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
	srand(time(NULL));
    while(fr->object_counter)
	{
		mtx_lock(fr->previous_mutex);
		remove_from_queue(fr->previous_queue, &automobile);
		mtx_unlock(fr->previous_mutex);
		fr->func(automobile);
		add_to_queue(fr->current_queue, automobile);
		fr->object_counter--;
		automobile = NULL;
	}
	return SUCCESS;
}

void fill_fr(function_resourse_t *fr, mtx_t *mutexes, thread_resource_t *resources)
{
	for (int i = 0; i < AUTOMOBILE_COUNT; i++)
		resources->array[i] = malloc(sizeof(automobile_t));
	resources->object_counter = AUTOMOBILE_COUNT;
    fr->current_mutex = mutexes;
    fr->func = add_number;
    (fr + 1)->func = create_body;
    (fr + 2)->func = create_circles;
    (fr + 3)->func = color_automobile;
    (fr + RESOURCES_COUNT - 2)->func = print_automobile;
    (fr + RESOURCES_COUNT - 2)->object_counter = AUTOMOBILE_COUNT;
    for (int i = 1; i < RESOURCES_COUNT - 2; i++)
    {
        (fr + i)->previous_mutex = mutexes + i - 1;
        (fr + i)->current_mutex = mutexes + i;
    }
	for (int i = 0; i < RESOURCES_COUNT - 1; i++)
	{
		(fr + i)->previous_queue = resources + i;
		(fr + i)->current_queue = resources + i + 1;
	}
    (fr + RESOURCES_COUNT - 2)->previous_mutex = mutexes + RESOURCES_COUNT - 3;
}
