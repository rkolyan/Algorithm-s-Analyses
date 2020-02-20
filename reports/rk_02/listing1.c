#include "dictionary.h"
#include <stdlib.h>

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
