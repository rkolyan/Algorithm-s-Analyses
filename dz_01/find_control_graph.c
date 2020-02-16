#include "find_control_graph.h"
#include "func_string.h"
#include <string.h>

static error_t find_size_of_block(char **strings, int count, int *result);
static error_t connect_conditions(char **strings, int count, graph_vertice_t *graph);
static error_t connect_cycles(char **strings, int count, graph_vertice_t *graph);

error_t find_control_graph(char **strings, int count, graph_vertice_t *graph)
{
	if (!strings || count <= 0 ||!graph)
		return ERROR_INPUT;
	char flag_of_cycle = 0, flag_of_condition = 0;
	int tmp_result = 0;

	for (int i = 0; i < count; i++)
	{
		flag_of_cycle = 0;
		flag_of_condition = 0;

		is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "for ", 4, &tmp_result);
		if (tmp_result >= 0)
			flag_of_cycle = 1;
		is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "while ", 6, &tmp_result);
		if (tmp_result >= 0)
			flag_of_cycle = 1;
		is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "do ", 3, &tmp_result);
		if (tmp_result >= 0)
			flag_of_cycle = 1;
		is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "else ", 3, &tmp_result);
		if (tmp_result >= 0)
			continue;
		is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "{", 1, &tmp_result);
		if (tmp_result >= 0)
			continue;
		is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "}", 1, &tmp_result);
		if (tmp_result >= 0)
			continue;
		is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "if ", 3, &tmp_result);
		if (tmp_result >= 0)
			flag_of_condition = 1;

		if (flag_of_cycle)
			connect_cycles(strings + i, count - i, graph + i);
		else if (flag_of_condition)
			connect_conditions(strings + i, count - i, graph + i);
		else if (i < count - 1)
			connect_graph_from_to(graph + i, graph + i + 1);
	}
	return SUCCESS;
}

static error_t connect_conditions(char **strings, int count, graph_vertice_t *graph)
{
	if (!strings || count <= 0 || !graph)
		return ERROR_INPUT;
	int tmp_result = 0;
	if (find_size_of_block(strings + 1, 0, &tmp_result) == ERROR_INCORRECT)
		return ERROR_INCORRECT;
	connect_graph_from_to(graph, graph + 1);
	int counter = tmp_result + 1;
	int repeating = 0;
	while (tmp_result != -1)
	{
		is_needle_in_haystack_usual(strings[counter], strlen(strings[counter]), "else if ", 8, &tmp_result);
		if (tmp_result != -1)
		{
			if (find_size_of_block(strings + counter, 0, &tmp_result) == ERROR_INCORRECT)
				return ERROR_INCORRECT;
			counter += tmp_result;
			repeating++;
		}
	}
	is_needle_in_haystack_usual(strings[counter], strlen(strings[counter]), "else ", 5, &tmp_result);
	if (tmp_result != -1)
		counter += tmp_result + 1;
	connect_graph_from_to(graph, graph + counter);

	int substractor = counter - tmp_result - 1;
	for (int i = 0; i < repeating; i++)
	{
		find_size_of_block(strings + substractor, 1, &tmp_result);
		connect_graph_from_to(graph + substractor, graph + counter);
		substractor -= tmp_result + 1;
	}

	return SUCCESS;
}

static error_t connect_cycles(char **strings, int count, graph_vertice_t *graph)
{
	if (!strings || !count || !graph)
		return ERROR_INPUT;
	int tmp_result = 0;
	//Первый элемент должен указывать на строку с оператором цикла, graph должен указывать на текущую цифру
	if (find_size_of_block(strings + 1, count - 1, &tmp_result) == ERROR_INCORRECT)
		return ERROR_INCORRECT;
	connect_graph_from_to(graph, graph + 1);
	connect_graph_from_to(graph + 1, graph + 2);
	connect_graph_from_to(graph + tmp_result, graph);
	if (tmp_result + 1 < count)
		connect_graph_from_to(graph + tmp_result, graph + tmp_result + 1);
	return SUCCESS;
}

static error_t find_size_of_block(char **strings, int invert, int *result)
{
	if (!strings || !result)
		return ERROR_INPUT;

	int tmp_result = 0, closure_count = 0, i = 0;

	if (!invert)
	{
		is_needle_in_haystack_usual(strings[0], strlen(strings[0]), "{", 1, &tmp_result);
		closure_count++;
		for (i = 2; closure_count > 0; i++)
		{
			is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "{", 1, &tmp_result);
			if (tmp_result >= 0)
				closure_count++;
			is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "}", 1, &tmp_result);
			if (tmp_result >= 0)
				closure_count--;
		}
		*result = i;
	}
	else
	{
		is_needle_in_haystack_usual(strings[0], strlen(strings[0]), "}", 1, &tmp_result);
		closure_count--;
		for (i = -2; closure_count < 0; i--)
		{
			is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "{", 1, &tmp_result);
			if (tmp_result >= 0)
				closure_count++;
			is_needle_in_haystack_usual(strings[i], strlen(strings[i]), "}", 1, &tmp_result);
			if (tmp_result >= 0)
				closure_count--;
		}
		*result = -i;
	}

	if (closure_count != 0)
		return ERROR_INCORRECT;
	return SUCCESS;
}
