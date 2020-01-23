#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_codes.h"
#include "func_string.h"
#include "list.h"

int main(int args_count, char **strings)
{
	if (args_count != 3)
	{
		puts("Вы должны ввести команду вида:\n./app.exe haystack needle");
		return SUCCESS;
	}
	int hlength = 0, nlength = 0;
	int *prefix_array = NULL, *shift_array = NULL, *suffix_array = NULL;
	list_t *list_head1 = NULL, *list_head2 = NULL, *list_head3 = NULL, *list_head4 = NULL;
	
	hlength = strlen(strings[1]);
	nlength = strlen(strings[2]);
	if (hlength < nlength)
	{
		puts("Длина образца должна быть не больше, чем длина основной строки!");
		return SUCCESS;
	}
	is_needle_in_haystack_usual(strings[1], hlength, strings[2], nlength, &list_head1);
	shift_array = malloc(sizeof(int) * SHIFT_ARRAY_SIZE);
	suffix_array = malloc(sizeof(int) * (nlength + 1));
	is_needle_in_haystack_boyer_mur(strings[1], hlength, strings[2], nlength, suffix_array, &list_head2);
	is_needle_in_haystack_boyer_mur_horpuskul(strings[1], hlength, strings[2], nlength, shift_array, &list_head3);
	free(suffix_array);
	free(shift_array);
	prefix_array = malloc(sizeof(int) * nlength);
	is_needle_in_haystack_knut_morris_prat(strings[1], hlength, strings[2], nlength, prefix_array, &list_head4);
	free(prefix_array);
	printf("list of positions find by usual:\t\t");
	print_list(list_head1);
	printf("list of positions find by boyer-mur:\t\t");
	print_list(list_head2);
	printf("list of positions find by horpuskull:\t\t");
	print_list(list_head3);
	printf("list of positions find by knut-morris-prat:\t");
	print_list(list_head4);
	delete_list(&list_head1);
	delete_list(&list_head2);
	delete_list(&list_head3);
	delete_list(&list_head4);

	return SUCCESS;
}
