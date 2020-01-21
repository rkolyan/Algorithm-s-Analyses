#include "io.h"
#include "dictionary.h"
#include <stdio.h>

int main(int argument_count, char **arguments)
{
	if (argument_count != 3)
	{
		puts("The command must be looked like:\n./app.exe WORDS TEXT");
		return 0;
	}

	dictionary_t **dictionary = NULL;
	FILE *file = NULL;
	file = fopen(arguments[1], "r");
	if (!file)
	{
		printf("File %s is not existed\n", arguments[1]);
		return 0;
	}
	fill_dictionary_from_file(&dictionary, file);
	fclose(file);
	file = fopen(arguments[2], "r");
	if (!file)
	{
		printf("File %s is not existed\n", arguments[2]);
		fclose(file);
		return 0;
	}
	read_and_print_not_in_dictionary(dictionary, file);	
	fclose(file);
	delete_dictionary(dictionary, ALPHABET_SIZE);
	return 0;
}
