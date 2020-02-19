#ifndef IO_H
#define IO_H

#include "error_codes.h"

#define BUFFER_SIZE 10000

error_t create_and_input_strings(char **strings, int count);

#endif
