#ifndef FUNC_FILE_H
#define FUNC_FILE_H

#include "error_codes.h"
#include <stdio.h>

error_t input_from_file(FILE *file, char ***strings, int *vertice_count);

#endif
