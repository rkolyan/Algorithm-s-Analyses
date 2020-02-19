#include "dictionary.h"
#include <stdlib.h>

static char return_symbol_delta_code(char symbol)
{
	if (symbol >= 'a' && symbol <= 'z')
		return symbol - 'a';
	else if (symbol >= 'A' && symbol <= 'Z')
		return symbol - 'A';
	return -1;
}

static void fill_dictionary_default(dictionary_t *element)
{
		element->count = 0;
		element->is_next_null = 0;
		for (int i = 0; i < ALPHABET_SIZE; i++)
			element->next_symbol_positions[i] = 0;
		element->nexts = NULL;
}

static dictionary_t *update_dictionary_node_and_return_next(dictionary_t *dictionary, int symbol_position)
{
	dictionary_t **nexts = malloc(sizeof(dictionary_t *) * (dictionary->count + 1));
	if (!nexts)
		return NULL;
	for (int i = 0; i < dictionary->count; i++)
		nexts[i] = dictionary->nexts[i];
	nexts[dictionary->count] = malloc(sizeof(dictionary_t));
	if (!nexts[dictionary->count])
	{
		free(nexts);
		return NULL;
	}
	dictionary->count++;
	dictionary->next_symbol_positions[symbol_position] = dictionary->count;
	free(dictionary->nexts);
	dictionary->nexts = nexts;
	return dictionary->nexts[dictionary->count - 1];
}

error_t add_word_to_dictionary(dictionary_t ***dictionary, char *word, int length)
{
	if (!dictionary || !word || !length)
		return ERROR_INPUT;
	
	int delta_symbol = return_symbol_delta_code(*word);
	int position = 0;

	if (delta_symbol == -1)
		return ERROR_INCORRECT;

	if (!*dictionary)
	{
		*dictionary = malloc(sizeof(dictionary_t *) * ALPHABET_SIZE);
		if (!*dictionary)
			return ERROR_ALLOCATE;
		for (int i = 0; i < ALPHABET_SIZE; i++)
			(*dictionary)[i] = NULL;
	}
	
	dictionary_t *current_node = NULL;
	if (!(*dictionary)[delta_symbol])
	{
		(*dictionary)[delta_symbol] = malloc(sizeof(dictionary_t));
		if (!(*dictionary)[delta_symbol])
			return ERROR_ALLOCATE;
		fill_dictionary_default((*dictionary)[delta_symbol]);
	}
	current_node = (*dictionary)[delta_symbol];

	for (int i = 1; i < length; i++)
	{
		delta_symbol = return_symbol_delta_code(word[i]);
		if (delta_symbol == -1)
			return ERROR_INCORRECT;
		if ((position = current_node->next_symbol_positions[delta_symbol]))
		{
			current_node = current_node->nexts[position - 1];
		}
		else
		{
			current_node = update_dictionary_node_and_return_next(current_node, delta_symbol);
			if (!current_node)
				return ERROR_ALLOCATE;
			fill_dictionary_default(current_node);
		}
	}
	current_node->is_next_null = 1;
	return SUCCESS;
}

error_t delete_dictionary(dictionary_t **dictionary, int count)
{
	if (!dictionary)
		return ERROR_INPUT;
	
	for (int i = 0; i < count; i++)
	{
		if (dictionary[i] != NULL)
		{
			if (dictionary[i]->nexts)
				delete_dictionary(dictionary[i]->nexts, dictionary[i]->count);
			free(dictionary[i]);
		}
	}
	if (count != 0)
		free(dictionary);
	return SUCCESS;
}

error_t find_position_and_length_of_maximum_substring(dictionary_t **dictionary, char *string, int length, int *sposition, int *slength)
{
	if (!dictionary || !string || !sposition || !length || !slength)
		return ERROR_INPUT;

	int max_position = -1, max_length = 0;
	int current_length = 0, current_position = -1;
	char flag = 0;
	dictionary_t *current_node = NULL;

	for (int i = 0; i < length - 1; i++)
	{
		if (!flag)
		{
			current_node = dictionary[(int)return_symbol_delta_code(string[i])];
			if (current_node)
			{
				current_length = 1;
				current_position = i;
				if (current_node->next_symbol_positions[(int)return_symbol_delta_code(string[i + 1])])
					flag = 1;
			}
			else
			{
				current_length = 0;
			}
		}
		else
		{
			current_node = current_node->nexts[current_node->next_symbol_positions[(int)return_symbol_delta_code(string[i])] - 1];
			current_length++;
			if (!current_node->next_symbol_positions[(int)return_symbol_delta_code(string[i + 1])])
				flag = 0;
		}
		if (current_length > max_length)
		{
			max_length = current_length;
			max_position = current_position;
		}
	}
	if (flag)
		current_length++;
	*sposition = max_position;
	*slength = max_length;
	return SUCCESS;
}
