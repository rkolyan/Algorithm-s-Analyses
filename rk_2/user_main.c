#include <stdio.h>

int main(void)
{
	int strings_count = 0;
	char **strings = NULL, char *result_string = NULL;
	printf("Введите кол-во строк:");
	scanf("%d", &strings_count);
	strings = malloc(sizeof(char *) * strings_count);
	create_and_input_strings(strings, strings_count);
	//TODO: Create new string
	printf("Результирующая строка:%s", result_string);
	free(result_string);
	free(strings);
	return 0;
}
