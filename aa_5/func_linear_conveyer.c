#include "func_linear_conveyer.h"

error_t begin_linear_conveyer(void *function_resourse)
{
	function_resourse_t *fr = function_resourse;
	if (!fr->func || !fr->previous_queue || !fr->current_queue)
		return ERROR_INPUT;
	automobile_t *automobile = NULL;
	srand(time(NULL));
	while(fr->previous_queue->object_counter)
	{
		remove_from_queue(fr->previous_queue, &automobile);
		fr->func(automobile);
		add_to_queue(fr->current_queue, automobile);
		fr->previous_queue->object_counter--;
	}
	return SUCCESS;
}
