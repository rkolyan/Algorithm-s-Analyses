#ifndef IO_H
#define IO_H

#include <time.h>
#include "error_codes.h"

error_t open_files(int threads_count);
error_t write_in_files(clock_t value1, clock_t value2, clock_t value3, clock_t value4);
error_t close_files(void);

#endif
