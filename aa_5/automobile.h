#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#define CIRCLE_VARIANTS_COUNT 4
#define BODY_VARIANTS_COUNT 6
#define COLOR_VARIANTS_COUNT 7

#define AUTOMOBILE_COUNT 20000

#include <time.h>

typedef int detail_t;
typedef int color_id_t;

typedef struct automobile
{
	clock_t time_marks[8];
	detail_t circles;
	detail_t body;
	color_id_t color;
	unsigned int number;
} automobile_t;

#endif
