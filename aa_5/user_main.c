#include <stdlib.h>
#include "func_conveyer.h"
#include "func_thread_conveyer.h"
#include "io.h"
#include "thread_resources.h"

int main(void)
{
    thread_resource_t *all_resources = NULL;
    mtx_t *mutexes = NULL;
    thrd_t *threads = NULL;
    function_resourse_t *fr = NULL;

    create_thread_resources_array(&all_resources, RESOURCES_COUNT);
    mutexes = calloc(RESOURCES_COUNT - 1, sizeof(mtx_t));
    fr = calloc(RESOURCES_COUNT - 1, sizeof (function_resourse_t));
    threads = calloc(RESOURCES_COUNT - 1, sizeof (thrd_t));
	fill_fr(fr, mutexes, all_resources);
    for (int i = 0; i < RESOURCES_COUNT - 1; i++)
        mtx_init(mutexes + i, mtx_plain | mtx_recursive);

    thrd_create(threads, begin_first_conveyer, fr);
    for (int i = 1; i < RESOURCES_COUNT - 2; i++)
        thrd_create(threads + i, begin_conveyer, fr + i);
    thrd_create(threads + RESOURCES_COUNT - 2, begin_last_conveyer, fr + RESOURCES_COUNT - 2);
    thrd_join(*threads, NULL);
    thrd_join(threads[RESOURCES_COUNT - 2], NULL);

    for (int i = 0; i < RESOURCES_COUNT - 1; i++)
        mtx_destroy(mutexes + i);
    free(mutexes);
    free_thread_resources_array(all_resources, RESOURCES_COUNT);
    free(fr);
    free(threads);
	return 0;
}

