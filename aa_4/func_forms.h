#ifndef FUNC_FORMS_H
#define FUNC_FORMS_H

#include <threads.h>
#include "error_codes.h"

typedef struct
{
	char id;
	union
	{
		error_t (*vinograd_function)(double *, double *, double *, double *, int, int, int, int, thrd_t *, int, double *);
		error_t (*standard_function)(double *, double *, int, int, int, int, thrd_t *, int, double *);
	};
} function_t;

#endif
