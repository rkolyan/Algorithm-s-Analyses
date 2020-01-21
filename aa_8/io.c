#include "io.h"
#include <stdlib.h>
#include <string.h>

#define STRING_BUFFER 200

error_t fill_dictionary_from_file(dictionary_t ***dictionary, FILE *file)
{
	if (!dictionary || !file)
		return ERROR_INPUT;
	char *string = NULL;
	int length = 0;
	string = malloc(sizeof(char) * STRING_BUFFER);
	while(fgets(string, STRING_BUFFER, file))
	{
		length = strlen(string);
		if (add_word_to_dictionary(dictionary, string, length - 2) == ERROR_ALLOCATE)
			return ERROR_ALLOCATE;
	}
	free(string);
	return SUCCESS;
}

error_t read_and_print_not_in_dictionary(dictionary_t **dictionary, FILE *file)
{
	if (!dictionary || !file)
		return ERROR_INPUT;
	char *word = NULL, symbol = '\0', result = 0, fact = 0;
	size_t length = 0;
	puts("All strings not in dictionary:");
	while (getdelim(&word, &length, ' ', file) >= 0)
	{
		if (length && word)
		{
			length = strlen(word);
			symbol = word[length - 1];
			fact = 1;
			while (fact)
			{
				fact = 0;
				if (symbol == ':' || symbol == ';' || symbol == ',' || symbol == ' ' || symbol == '\n' ||
						symbol == '\t' || symbol == '.' || symbol == '?' || symbol == '!' || 
						symbol == '\'' || symbol == '\"')
				{
					fact = 1;
					length--;
				}
				symbol = word[length - 1];
			}
			is_word_in_dictionary(dictionary, word, length, &result);
			if (!result)
				puts(word);
		}
		free(word);
		word = NULL;
	}
	if (word)
		free(word);
	return SUCCESS;
}
