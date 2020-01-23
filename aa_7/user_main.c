#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_codes.h"
#include "func_string.h"

int main(int args_count, char **strings)
{
	if (args_count != 3)
	{
		puts("Вы должны ввести команду вида:\n./app.exe haystack needle");
		return SUCCESS;
	}
	int hlength = 0, nlength = 0, result1 = 0, result2 = 0, result3 = 0, result4 = 0;
	int *prefix_array = NULL, *shift_array = NULL, *suffix_array = NULL;
	
	hlength = strlen(strings[1]);
	nlength = strlen(strings[2]);
	if (hlength < nlength)
	{
		puts("Длина образца должна быть не больше, чем длина основной строки!");
		return SUCCESS;
	}
	is_needle_in_haystack_usual(strings[1], hlength, strings[2], nlength, &result1);
	shift_array = malloc(sizeof(int) * SHIFT_ARRAY_SIZE);
	suffix_array = malloc(sizeof(int) * (nlength + 1));
	is_needle_in_haystack_boyer_mur(strings[1], hlength, strings[2], nlength, suffix_array, &result2);
	is_needle_in_haystack_boyer_mur_horpuskul(strings[1], hlength, strings[2], nlength, shift_array, &result3);
	free(suffix_array);
	free(shift_array);
	prefix_array = malloc(sizeof(int) * nlength);
	is_needle_in_haystack_knut_morris_prat(strings[1], hlength, strings[2], nlength, prefix_array, &result4);
	free(prefix_array);
	printf("result of \tusual = %d\n\t\tboyer_mur = %d\n\t\tboyer_mur_horpuskul = %d\n\t\tkmp = %d\n", result1 + 1, result2 + 1, result3 + 1, result4 + 1);
	return SUCCESS;
}
