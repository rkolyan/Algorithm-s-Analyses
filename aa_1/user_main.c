#include "func_distance.h"
#include "printing_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 200

int main(int argc, char **argv)
{
	unsigned int *matr = NULL, result = 0;
	char *s1 = malloc(sizeof(char) * STR_LEN);
	char *s2 = malloc(sizeof(char) * STR_LEN);
	while (1)
	{
		printf("Хотите продолжить выполнение?[y/(n)]:");
		fgets(s1, STR_LEN, stdin);
		if (s1[0] != 'y')
			break;
		printf("Введите s1:");
		fgets(s1, STR_LEN, stdin);
		printf("Введите s2:");
		fgets(s2, STR_LEN, stdin);
		int l1 = strlen(s1) - 1;
		int l2 = strlen(s2) - 1;
		s1[l1] = '\0';
		s2[l2] = '\0';
		matr = calloc((l1 + 2) * (l2 + 1), sizeof(unsigned int));
		find_levenstein_distance_matrix_sum_version(s1, s2, l1, l2, &result, matr);
		printf("Расстояние Левенштейна (обычный алгоритм) между s1 и s2 = %u\n", result);
		print_matrix(matr, l1, l2, s1, s2);
		find_levenstein_distance_recursive(s1, s2, l1, l2, &result);
		printf("Расстояние Левенштейна (рекурсивный алгоритм) между s1 и s2 = %u\n", result);
		find_levenstein_distance_modified_matrix_version(s1, s2, l1, l2, &result, matr);
		printf("Расстояние Левенштейна (модифицированный алгоритм) между s1 и s2 = %u\n", result);
		free(matr);
	}
	free(s1);
	free(s2);
	return 0;
}
