#ifndef FUNC_FORMS_H
#define FUNC_FORMS_H

#include "error_codes.h"

typedef struct
{
	char type;
	union
	{
		error_t (multithread_function*)(void);//TODO:Exchange void on parameters
		error_t (linear_version*)(void);
	}
} function_t;

#endif
