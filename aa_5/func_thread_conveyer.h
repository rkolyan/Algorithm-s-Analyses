#ifndef FUNC_THREAD_CONVEYER_H
#define FUNC_THREAD_CONVEYER_H

#include "func_conveyer.h"
#include "thread_resources.h"
#include <threads.h>

typedef struct
{
    error_t (*func)(automobile_t *);
    thread_resource_t *previous_queue;
    thread_resource_t *current_queue;
    mtx_t *previous_mutex;
    mtx_t *current_mutex;
    unsigned int counter;
} function_resourse_t;

error_t begin_first_conveyer(function_resourse_t *fr);
error_t begin_conveyer(function_resourse_t *fr);
error_t begin_last_conveyer(function_resourse_t *fr);

#endif
