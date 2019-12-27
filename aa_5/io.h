#ifndef IO_H
#define IO_H

#include "automobile.h"
#include "error_codes.h"

void open_output(void);
error_t print_automobile(automobile_t *automobile);
void close_output(void);

#endif
