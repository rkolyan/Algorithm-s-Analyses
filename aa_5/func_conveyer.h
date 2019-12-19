#ifndef FUNC_CONVEYER_H
#define FUNC_CONVEYER_H

#include "error_codes.h"
#include "automobile.h"

error_t create_body(automobile_t *automobile);
error_t create_circles(automobile_t *automobile);
error_t add_number(automobile_t *automobile);
error_t color_automobile(automobile_t *automobile);

#endif
