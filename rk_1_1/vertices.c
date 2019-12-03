#include <stdlib.h>
#include "vertices.h"

error_t create_array_of_vertices(type_t *array, int count, vertice_t **varray)
{
	if (!array || !count || !varray)
		return ERROR_INPUT;

	int count1 = 0;
	vertice_t *tmp_varray = NULL;
	tmp_varray = malloc(sizeof(vertice_t) * count);
	if (!tmp_varray)
		return ERROR_ALLOCATE;
	for (int i = 0; i < count; i++, count1 = 0)
	{
		for (int j = 0; j < count; j++)
		{
			if (i != j && (array[i * count + j]))
				count1++;
		}
		tmp_varray[i]->vertice_count = count1;
		if (count1 != 0)
			(tmp_varray + i)->array = malloc(sizeof(int) * count1);
		else
			(tmp_varray + i)->array = NULL;
		tmp_varray[i]->num = i;
		count1 = 0;
		for (int j = 0; j < count; j++)
		{
			if (i != j && (array[i * count + j]))
			{
				((tmp_varray + i)->array)[count1] = j;
				count1++;
			}
		}
	}
	*varray = tmp_varray;
	return SUCCESS;
}

error_t create_file(vertice_t *varray, int count)
{
	if (!varray || !count)
		return ERROR_INPUT;

	FILE *file = fopen("res.dot", "w");
	fprintf(f, "digraph res\n{\n");
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < (varray + i)->vertice_count; j++)
			fprintf(f, "\t%d -> %d;\n", i + 1, ((varray + i)->array)[j]->num + 1);
	}
	fprintf(f, "}\n");
	fclose(f);

	return SUCCESS;
}

error_t remove_array_of_vertices(vertice_t **varray, int *count)
{
	if (!varray || !count)
		return ERROR_INPUT;

	for (int i = 0; i < *count; i++)
	{
		free((*varray + i)->array);
	}
	free(*varray);
	*varray = NULL;
	*count = 0;
	return SUCCESS;
}
