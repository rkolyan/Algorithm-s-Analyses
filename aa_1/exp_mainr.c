#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func_distance.h"
#include "func_analys.h"
#include "func_forms.h"

void find_calculations(int count1, int count2, function_t *functions, const char *filename)
{
	clock_t clocks = 0;
	FILE *file = NULL;
	char *s1 = NULL, *s2 = NULL;
	int length1 = 0, length2 = 0;
	file = fopen(filename, "w");
	for (int i = 1; i <= count1; i++)
	{
		for (int j = 0; j < count2; j++)
		{
			s1 = create_random_word_with_size(i);
			s2 = create_random_word_with_size(i);
			length1 = strlen(s1);
			length2 = strlen(s2);
			clocks += find_time(s1, s2, length1, length2, functions);
			free(s1);
			free(s2);
		}
		clocks /= count2;
		fprintf(file, "%ld\n", clocks);
	}
	fclose(file);
}

int main(void)
{
	int count1 = 0, count2 = 0;

	printf("Введите максимальное кол-во символов:");
	scanf("%d", &count1);
	printf("Введите максимальное кол-во итераций:");
	scanf("%d", &count2);

	function_t *functions = malloc(sizeof(function_t));
	functions->function = find_levenstein_distance_recursive;
	functions->id = 0;
	find_calculations(count1, count2, functions, "calculations/recursive_levenstein_results.txt");
	free(functions);
	return 0;
}
