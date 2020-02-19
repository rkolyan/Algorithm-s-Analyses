#include <stdio.h>

#define STRINGS_COUNT 2

int main(void)
{
	char (*strings)[STRINGS_COUNT] = {NULL};
	create_and_input_strings(strings, STRINGS_COUNT);
	//TODO:Написать функцию препроцессинга
	//TODO:Написать функцию, которая находит наибольший совпавший промежуток
	return 0;
}
