#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

error_t create_and_input_strings(char **strings, int count)
{
	if (!strings || !count)
		return ERROR_INPUT;
	char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
	for (int i = 0; i < count; i++)
	{
		printf("Введите %d-ю строку:", i + 1);
		fgets(buffer, BUFFER_SIZE, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		strings[i] = strdup(buffer);
	}
	free(buffer);
	return SUCCESS;
}
