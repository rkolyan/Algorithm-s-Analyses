#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

error_t add_word_to_dictionary(dictionary_t ***dictionary, char *word)
{
	if (!dictionary || !word)
		return ERROR_INPUT;
	if (!*dictionary)
	{
		*dictionary = malloc(sizeof(dictionary_t *) * ALPHABET_SIZE);
		if (!*dictionary)
			return ERROR_ALLOCATE;
		for (int i = 0; i < ALPHABET_SIZE; i++)
			(*dictionary)[i] = NULL;
	}
	
	int length = strlen(word);
	if (!length)
		return SUCCESS;

	dictionary_t *current_node = malloc(sizeof(dictionary_t));
	if (!current_node)
		return ERROR_ALLOCATE;
	if (*word >= 'a' && *word <= 'z')
	{
		(*dictionary)[*word - 'a'] = current_node;
	}
	else if (*word >= 'A' && *word <= 'Z')
	{
		(*dictionary)[*word - 'A'] = current_node;
	}
	else 
	{
		free(current_node);
		return ERROR_INCORRECT;
	}
	current_node->nexts = NULL;
	current_node->is_next_0 = 0;

	for (int i = 1; i < length; i++)
	{
		current_node->nexts = malloc(sizeof(dictionary_t *) * ALPHABET_SIZE);
		if (!current_node->nexts)
			return ERROR_ALLOCATE;
		for (int i = j; i < ALPHABET_SIZE; i++)
			(current_node->nexts)[j] = NULL;
		if (word[i] >= 'a' && word[i] <= 'z')
		{
			(current_node->nexts)[word[i] - 'a'] = malloc(sizeof(dictionary_t));
			if (!(current_node->nexts)[word[i] - 'a'])
				return ERROR_ALLOCATE;
			current_node = (current_node->nexts)[word[i] - 'a'];
		}
		else if (word[i] >= 'A' && word[i] <= 'Z')
		{
			(current_node->nexts)[word[i] - 'A'] = malloc(sizeof(dictionary_t));
			if (!(current_node->nexts)[word[i] - 'A'])
				return ERROR_ALLOCATE;
			current_node = (current_node->nexts)[word[i] - 'A'];
		}
		current_node->nexts = NULL;
		current_node->is_next_0 = 0;
	}
	current_node->is_next_0 = 1;
	return SUCCESS;
}

error_t delete_dictionary(dictionary_t **dictionary)
{
	if (!dictionary)
		return ERROR_INPUT;
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (dictionary[i] != NULL)
		{
			if (dictionary[i]->nexts)
				delete_dictionary(dictionary[i]->nexts);
		}
		free(dictionary[i]);
	}
	free(dictionary);
	return SUCCESS;
}
