#ifndef FUNC_THREAD_CONVEYER_H
#define FUNC_THREAD_CONVEYER_H

#include "func_conveyer.h"
#include "thread_resources.h"

error_t begin_first_conveyer(error_t (func*)(automobile_t *), thread_resource_t *previous_queue, thread_resource_t *current_queue);
error_t begin_conveyer(error_t (func*)(automobile_t *), thread_resource_t *previous_queue, thread_resource_t *current_queue);

#endif
