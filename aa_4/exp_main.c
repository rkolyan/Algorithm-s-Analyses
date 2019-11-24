#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func_matrix_mult.h"
#include "func_analys.h"
#include "func_forms.h"

int main(void)
{
	int count1 = 0, count2 = 0, threads_count = 0;

	printf("Введите максимальную длину строноны:");
	scanf("%d", &count1);
	printf("Введите максимальное кол-во итераций:");
	scanf("%d", &count2);
	printf("Введите максимальное кол-во потоков:");
	scanf("%d", &threads_count);

	function_t *functions = malloc(sizeof(function_t));

	functions->id = 0;
	functions->standard_function = standard_multiply_matrix;
	find_calculations(count1, count2, threads_count, functions, "calculations/standard_multiply.txt");
	puts("1 is ready");
	functions->id = 1;
	//functions->vinograd_function = vinograd_multiply_matrix;
	//find_calculations(count1, count2, threads_count, functions, "calculations/vinograd_multiply.txt");
	//puts("2 is ready");
	free(functions);
	return 0;
}
