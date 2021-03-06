#include "function_resources.h"
#include "func_thread_conveyer.h"
#include <stdlib.h>

error_t begin_last_conveyer(void *function_resource)
{
	function_resource_t *fr = function_resource;
	if (!fr->func || !fr->previous_queue || !fr->current_queue || !fr->previous_mutex || !fr->previous_cond)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
	srand(time(NULL));
	for (int i = 0; i < AUTOMOBILE_COUNT; i++)
	{
		mtx_lock(fr->previous_mutex);
		if (!is_not_empty(fr->previous_queue))
			cnd_wait(fr->previous_cond, fr->previous_mutex);
		remove_from_queue(fr->previous_queue, &automobile);
		mtx_unlock(fr->previous_mutex);

		fr->func(automobile);//Call function

		add_to_queue(fr->current_queue, automobile);
		automobile = NULL;
	}
	return SUCCESS;
}
