#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "error_codes.h"
#include "func_analys.h"
#include "func_forms.h"
#include "func_sort.h"

void find_calculations(int count1, int count2, function_p function, error_t (*fill_array)(type_t *, int), const char *filename)
{
	clock_t clocks = 0;
	FILE *file = NULL;
	type_t *array = NULL;

	srand(time(NULL));
	file = fopen(filename, "w");
	array = malloc(sizeof(type_t) * count1);
	for (int i = 1; i <= count1; i++)
	{
		clocks = 0;
		for (int j = 0; j < count2; j++)
		{
			fill_array(array, i);
			clocks += find_time(array, i, function);
		}
		clocks /= count2;
		fprintf(file, "%ld\n", clocks);
	}
	free(array);
	fclose(file);
}

#define col1 row2
clock_t find_time(type_t *array, int count, function_p function)
{
	clock_t timer;
	timer = clock();
	function(array, count);
	timer = clock() - timer;
	return timer;
}

error_t fill_random_array_with_size(type_t *array, int count)
{
	if (count <= 0 || !array)
		return ERROR_INPUT;
	for (int i = 0; i < count; i++)
		array[i] = ((type_t)(rand() % 1000000)) / 1000;
	return SUCCESS;
}

static int compare1(const void *a, const void *b)
{
	return (*((type_t *)a) - *((type_t *)b));
}

static int compare2(const void *a, const void *b)
{
	return (*((type_t *)b) - *((type_t *)a));
}

error_t fill_unsorted_array_with_size(type_t *array, int count)
{
	if (count <= 0 || !array)
		return ERROR_INPUT;
	for (int i = 0; i < count; i++)
		array[i] = ((type_t)(rand() % 1000000)) / 1000;
	qsort(array, count, sizeof(type_t), compare2);
	return SUCCESS;
}

error_t fill_sorted_array_with_size(type_t *array, int count)
{
	if (count <= 0 || !array)
		return ERROR_INPUT;
	for (int i = 0; i < count; i++)
		array[i] = ((type_t)(rand() % 1000000)) / 1000;
	qsort(array, count, sizeof(type_t), compare1);
	return SUCCESS;
}
