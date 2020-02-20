#include "dictionary.h"
#include <stdlib.h>

error_t is_word_in_dictionary(dictionary_t **dictionary, char *word, int length, char *result)
{

	if (!dictionary || !word || !result)
		return ERROR_INPUT;
	if (!length)
		return SUCCESS;
	
	int delta_symbol = return_symbol_delta_code(*word);
	int position = 0;
	*result = 0;

	if (delta_symbol < 0)
		return SUCCESS;

	dictionary_t *current_node = dictionary[delta_symbol];
	if (!current_node)
		return SUCCESS;

	for (int i = 1; i < length; i++)
	{
		delta_symbol = return_symbol_delta_code(word[i]);
		if (delta_symbol == -1 || !(position = current_node->next_symbol_positions[delta_symbol]))
			return SUCCESS;
		current_node = current_node->nexts[position - 1];
	}

	if (current_node->is_next_null)
		*result = 1;

	return SUCCESS;
}
