#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func_sort.h"
#include "func_analys.h"
#include "func_forms.h"

int main(void)
{
	int count1 = 0, count2 = 0;

	printf("Введите максимальную длину массива:");
	scanf("%d", &count1);
	printf("Введите максимальное кол-во итераций:");
	scanf("%d", &count2);

	find_calculations(count1, count2, sort_min_max, fill_random_array_with_size, "calculations/sort_min_max_random.txt");
	puts("1 is ready");
	find_calculations(count1, count2, sort_min_max, fill_sorted_array_with_size, "calculations/sort_min_max_sorted.txt");
	puts("2 is ready");
	find_calculations(count1, count2, sort_min_max, fill_unsorted_array_with_size, "calculations/sort_min_max_unsorted.txt");
	puts("3 is ready");

	find_calculations(count1, count2, sort_bubble, fill_random_array_with_size, "calculations/sort_bubble_random.txt");
	puts("4 is ready");
	find_calculations(count1, count2, sort_bubble, fill_sorted_array_with_size, "calculations/sort_bubble_sorted.txt");
	puts("5 is ready");
	find_calculations(count1, count2, sort_bubble, fill_unsorted_array_with_size, "calculations/sort_bubble_unsorted.txt");
	puts("6 is ready");

	find_calculations(count1, count2, sort_shaker, fill_random_array_with_size, "calculations/sort_shaker_random.txt");
	puts("7 is ready");
	find_calculations(count1, count2, sort_shaker, fill_sorted_array_with_size, "calculations/sort_shaker_sorted.txt");
	puts("8 is ready");
	find_calculations(count1, count2, sort_shaker, fill_unsorted_array_with_size, "calculations/sort_shaker_unsorted.txt");
	puts("9 is ready");
	return 0;
}
