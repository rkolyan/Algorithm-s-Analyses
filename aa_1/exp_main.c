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
		clocks = 0;
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

	functions->id = 1;
	functions->matrix_function = find_levenstein_distance_matrix_version;
	find_calculations(count1, count2, functions, "calculations/levenstein_matrix_results.txt");
	puts("1 is ready");
	functions->matrix_function = find_levenstein_distance_modified_matrix_version;
	find_calculations(count1, count2, functions, "calculations/damerlau_levenstein_matrix_results.txt");
	puts("2 is ready");
	functions->matrix_function = find_levenstein_distance_matrix_sum_version;
	find_calculations(count1, count2, functions, "calculations/levenstein_matrix_sum_results.txt");
	puts("3 is ready");
	functions->matrix_function = find_levenstein_distance_modified_matrix_sum_version;
	find_calculations(count1, count2, functions, "calculations/damerlau_levenstein_matrix_sum_results.txt");
	puts("4 is ready");
	functions->id = 2;
	functions->matrix_function = find_levenstein_distance;
	find_calculations(count1, count2, functions, "calculations/levenstein_results.txt");
	puts("5 is ready");
	functions->matrix_function = find_levenstein_distance_modified;
	find_calculations(count1, count2, functions, "calculations/damerlau_levenstein_results.txt");
	puts("6 is ready");
	free(functions);
	return 0;
}
