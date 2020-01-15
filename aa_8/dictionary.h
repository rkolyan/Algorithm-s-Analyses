#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "error_codes.h"

typedef struct tree
{
	char symbol;
	struct tree **nexts;
	char is_next_0;
} dictionary_t;

error_t add_word_to_dictionary(dictionary_t **dictionary, char *word);
error_t delete_dictionary(dictionary_t **dictionary);

#endif
