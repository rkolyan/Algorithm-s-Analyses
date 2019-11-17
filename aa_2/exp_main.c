#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func_matrix_mult.h"
#include "func_analys.h"
#include "func_forms.h"

int main(void)
{
	int count1 = 0, count2 = 0;

	printf("Введите максимальную длину строноны:");
	scanf("%d", &count1);
	printf("Введите максимальное кол-во итераций:");
	scanf("%d", &count2);

	function_t *functions = malloc(sizeof(function_t));

	functions->id = 0;
	functions->standard_function = standard_multiply_matrix;
	find_calculations(count1, count2, functions, "calculations/standard_multiply.txt");
	puts("1 is ready");
	functions->standard_function = standard_multiply_matrix_optimized;
	find_calculations(count1, count2, functions, "calculations/standard_multiply_optimized.txt");
	puts("2 is ready");
	functions->id = 1;
	functions->vinograd_function = vinograd_multiply_matrix;
	find_calculations(count1, count2, functions, "calculations/vinograd_multiply.txt");
	puts("3 is ready");
	functions->vinograd_function = vinograd_multiply_matrix_optimized1;
	find_calculations(count1, count2, functions, "calculations/vinograd_multiply_optimized1.txt");
	puts("4 is ready");
	functions->vinograd_function = vinograd_multiply_matrix_optimized2;
	find_calculations(count1, count2, functions, "calculations/vinograd_multiply_optimized2.txt");
	puts("5 is ready");
	free(functions);
	return 0;
}
