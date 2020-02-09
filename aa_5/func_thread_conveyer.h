#ifndef FUNC_THREAD_CONVEYER_H
#define FUNC_THREAD_CONVEYER_H

#include "func_conveyer.h"
#include "memory_resources.h"

#define THREADS_COUNT 5

error_t begin_first_conveyer(void *function_resource);
error_t begin_conveyer(void *function_resource);
error_t begin_last_conveyer(void *function_resource);


#endif
