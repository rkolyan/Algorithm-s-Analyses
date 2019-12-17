#ifndef FUNC_FORMS_H
#define FUNC_FORMS_H

#include "error_codes.h"

typedef struct
{
	char id;
	union
	{
		error_t (*vinograd_function)(double **, double **, double *, double *, int, int, int, int, double **);
		error_t (*standard_function)(double **, double **, int, int, int, int, double **);
	};
} function_t;

#endif
