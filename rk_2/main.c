#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "io.h"

#define STRINGS_COUNT 2

int main(void)
{
	char **strings = NULL;
	int length = 0, sposition = -1, slength = 0;
	dictionary_t **dictionary = NULL;

	strings = malloc(sizeof(char *) * STRINGS_COUNT);
	create_and_input_strings((char **) strings, STRINGS_COUNT);
	length = strlen(strings[0]);
	for (int i = 0; i < length; i++)
		add_word_to_dictionary(&dictionary, strings[0] + i, length - i);

	find_position_and_length_of_maximum_substring(dictionary, strings[1], strlen(strings[1]), &sposition, &slength);

	puts(strings[0]);
	puts(strings[1]);
	snprintf(strings[0], slength + 1, "%s", strings[1] + sposition);
	puts(strings[0]);

	delete_dictionary(dictionary, ALPHABET_SIZE);
	free(strings[0]);
	free(strings[1]);
	free(strings);
	return 0;
}
