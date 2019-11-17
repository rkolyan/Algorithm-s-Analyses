#ifndef FUNC_FORMS_H
#define FUNC_FORMS_H

#include "error_codes.h"

typedef struct
{
	char id;
	union
	{
		error_t (*matrix_function)(char *, char *, int, int, unsigned int *, unsigned int *);
		error_t (*function)(char *, char *, int, int, unsigned int *);
	};
} function_t;

#endif
