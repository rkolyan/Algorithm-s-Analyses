#include "func_conveyer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

error_t create_body(automobile_t *automobile)
{
	if (!automobile)
		return ERROR_INPUT;
    automobile->body = rand() % BODY_VARIANTS_COUNT;
	//for (int i = 0; i < 100000; i++);
	return SUCCESS;
}

error_t create_circles(automobile_t *automobile)
{
    if (!automobile)
		return ERROR_INPUT;
	automobile->circles = rand() % CIRCLE_VARIANTS_COUNT;
	//for (int i = 0; i < 100000; i++);
	return SUCCESS;
}

error_t add_number(automobile_t *automobile)
{
	if (!automobile)
		return ERROR_INPUT;
	automobile->number = rand();
	//for (int i = 0; i < 100000; i++);
	return SUCCESS;
}

error_t color_automobile(automobile_t *automobile)
{
	if (!automobile)
		return ERROR_INPUT;
	automobile->color = rand() % COLOR_VARIANTS_COUNT;
	//for (int i = 0; i < 100000; i++);
	return SUCCESS;
}
