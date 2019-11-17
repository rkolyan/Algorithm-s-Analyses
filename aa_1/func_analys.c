#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "error_codes.h"
#include "func_forms.h"

clock_t find_time(char *s1, char *s2, int length1, int length2, function_t *functions)
{
	clock_t timer;
	if (functions->id != 0)
	{
		unsigned int result = 0, *matrix = NULL;
		if (functions->id == 1)
			matrix = calloc((length1 + 2) * (length2 + 1), sizeof(unsigned int));
		else
			matrix = calloc((length2 + 1) * 3, sizeof(unsigned int));
		timer = clock();
		functions->matrix_function(s1, s2, length1, length2, &result, matrix);
		timer = clock() - timer;
		free(matrix);
	}
	else
	{
		unsigned int result = 0;
		timer = clock();
		functions->function(s1, s2, length1, length2, &result);
		timer = clock() - timer;
	}
	return timer;
}

char *create_random_word_with_size(int size)
{
	char *word = NULL;
	word = malloc(sizeof(char) * (size + 1));
	for (int i = 0; i < size; i++)
		word[i] = rand() % ('z' - ' ') + ' ';
	word[size] = '\0';
	return word;
}
