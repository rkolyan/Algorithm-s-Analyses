#ifndef WAY_H
#define WAY_H

// структура ПУТЬ (длинна, массив вершин, количество вершин)
typedef struct
{
	int tabu_count;
	int length;
	int *tabu;
} way_t;

#endif
