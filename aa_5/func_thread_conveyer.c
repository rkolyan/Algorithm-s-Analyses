#include "func_thread_conveyer.h"

error_t begin_first_conveyer(void *function_resourse)
{
	function_resourse_t *fr = function_resourse;
	if (!fr->func || !fr->previous_queue || !fr->current_queue || !fr->current_mutex)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
	
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
	while(1)
	{
		mtx_lock(fr->previous_mutex);
		remove_from_queue(fr->previous_queue, &automobile);
		mtx_unlock(fr->previous_mutex);
		fr->func(automobile);
		mtx_lock(fr->current_mutex);
		add_to_queue(fr->current_queue, automobile);
		mtx_unlock(fr->current_mutex);
		fr->previous_queue->object_counter--;
	}
	return SUCCESS;
}

error_t begin_last_conveyer(void *function_resourse)
{
	function_resourse_t *fr = function_resourse;
    if (!fr->func || !fr->previous_queue || !fr->previous_mutex)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
    while(fr->object_counter)
	{
		mtx_lock(fr->previous_mutex);
		remove_from_queue(fr->previous_queue, &automobile);
		mtx_unlock(fr->previous_mutex);
		fr->func(automobile);
		add_to_queue(fr->previous_queue, automobile);
		fr->object_counter--;
	}
	return SUCCESS;
}
