#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#define CIRCLE_VARIANTS_COUNT 4
#define BODY_VARIANTS_COUNT 6
#define COLOR_VARIANTS_COUNT 7

typedef char detail_t;
typedef char color_id_t;

typedef struct automobile
{
	detail_t circles;
	detail_t body;
	color_id_t color;
	unsigned int number;
} automobile_t;

#endif
