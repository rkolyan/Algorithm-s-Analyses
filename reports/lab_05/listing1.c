#include "function_resources.h"
#include "func_thread_conveyer.h"
#include <stdlib.h>

error_t begin_first_conveyer(void *function_resource)
{
	function_resource_t *fr = function_resource;
	if (!fr->func || !fr->previous_queue || !fr->current_queue || !fr->current_mutex || !fr->current_cond)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
	srand(time(NULL));
	for (int i = 0; i < AUTOMOBILE_COUNT; i++)
	{
		remove_from_queue(fr->previous_queue, &automobile);

		fr->func(automobile);//Call function

		mtx_lock(fr->current_mutex);
		add_to_queue(fr->current_queue, automobile);
		cnd_signal(fr->current_cond);
		mtx_unlock(fr->current_mutex);
		automobile = NULL;
	}
	return SUCCESS;
}
