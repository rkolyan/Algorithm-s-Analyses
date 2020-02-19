#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "error_codes.h"

#define ALPHABET_SIZE 26

typedef struct tree
{
	unsigned char count : 5;
	char is_next_null : 3; // Можно и 1, но без разницы, можно ещё добавить какую-нибудь прикольную переменную
	char next_symbol_positions[ALPHABET_SIZE];
	struct tree **nexts;//массив размером от 0 до 26 (в зависимости от того сколько символов в следующей позиции)
} dictionary_t;

error_t add_word_to_dictionary(dictionary_t ***dictionary, char *word, int word_length);
error_t delete_dictionary(dictionary_t **dictionary, int count);
error_t find_position_and_length_of_maximum_substring(dictionary_t **dictionary, char *string, int length, int *sposition, int *slength);

#endif
