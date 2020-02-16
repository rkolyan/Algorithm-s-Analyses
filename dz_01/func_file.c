#include "func_file.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 500

error_t input_from_file(FILE *file, char ***strings, int *vertice_count)
{
	if (!file || !strings || !vertice_count)//Может внести файл?
		return ERROR_INPUT;
	*vertice_count = 0;
	char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return ERROR_ALLOCATE;
	
	while (fgets(buffer, BUFFER_SIZE, file))
		(*vertice_count)++;

	*strings = malloc(sizeof(char *) * (*vertice_count));
	if (!*strings)
	{
		free(buffer);
		return ERROR_ALLOCATE;
	}

	rewind(file);
	for (int i = 0; i < *vertice_count; i++)
	{
		fgets(buffer, BUFFER_SIZE, file);
		buffer[strlen(buffer) - 1] = '\0';
		(*strings)[i] = strdup(buffer);
	}
	free(buffer);

	return SUCCESS;
}
