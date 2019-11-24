#ifndef FUNC_FORMS_H
#define FUNC_FORMS_H

#include "error_codes.h"
#include "func_matrix_mult.h"

typedef struct
{
	char id;
	union
	{
		error_t (*vinograd_function)(double *, double *, double *, double *, int, int, int, int, thrd_t *, int, double *);
		error_t (*standard_function)(double *, double *, int, int, int, int, thrd_t *, int, function_resourse_t *, double *);
	};
} function_t;

#endif
