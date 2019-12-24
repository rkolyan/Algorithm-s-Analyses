#include "func_thread_conveyer.h"

error_t begin_first_conveyer(error_t (*func)(automobile_t *), thread_resource_t *previous_queue, thread_resource_t *current_queue, mtx_t *current_mutex)
{
	if (!func || !previous_queue || !current_queue || !current_mutex)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
	while(previous_queue->object_counter)
	{
        remove_from_queue(previous_queue, &automobile);
		func(automobile);
        mutex_lock(current_mutex);
        add_to_queue(current_queue, automobile);
		mutex_unlock(current_mutex);
		previous_queue->object_counter--;
	}
	return SUCCESS;
}

error_t begin_conveyer(error_t (*func)(automobile_t *), thread_resource_t *previous_queue, thread_resource_t *current_queue, mtx_t *previous_mutex, mtx_t *current_mutex)
{
	if (!func || !previous_queue || !current_queue || !previous_mutex || !current_mutex)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
	while(1)
	{
		mutex_lock(previous_mutex);
        remove_from_queue(previous_queue, &automobile);
		mutex_unlock(previous_mutex);
		func(automobile);
		mutex_lock(current_mutex);
        add_to_queue(current_queue, automobile);
		mutex_unlock(current_mutex);
		previous_queue->object_counter--;
	}
	return SUCCESS;
}

error_t begin_last_conveyer(error_t (*func)(automobile_t *), thread_resource_t *previous_queue, thread_resource_t *current_queue, mtx_t *previous_mutex, unsigned int object_counter)
{
    if (!func || !previous_queue || !previous_mutex)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
    while(object_counter)
	{
		mutex_lock(previous_mutex);
        remove_from_queue(previous_queue, &automobile);
		mutex_unlock(previous_mutex);
        func(automobile);
        add_to_queue(previous_queue, automobile);
        object_counter--;
	}
	return SUCCESS;
}
