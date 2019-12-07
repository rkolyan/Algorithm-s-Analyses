#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "matrix.h"
#include "vertices.h"
#include "clique.h"

int main(int argc, char **argv)
{
	type_t *matrix = NULL;
	FILE *file;
	int count = 0;
	vertice_t *varray = NULL;
	clique_stack_element_t *clique_stack = NULL;

	if (argc != 2)
		return ERROR_INPUT;
	
	file = fopen(argv[1], "r");
	if (!file)
		return ERROR_INCORRECT;

	if (create_matrix_from_file(file, &matrix, &count))
	{
		fclose(file);
		return ERROR_INCORRECT;
	}
	fclose(file);

	if (!is_graph_is_not_oriented(matrix, count))
	{
		free(matrix);
		return ERROR_INCORRECT;
	}

	create_vertices(matrix, count, &varray);
	find_cliques(varray, count, &clique_stack);
	remove_duplicates_from_stack(&clique_stack);
	print_cliques(varray, count, clique_stack);
	remove_clique_stack(&clique_stack);
	free(matrix);
	create_output_graph_file(varray, count);
	remove_vertices(&varray, &count);
	system("dot -Tpng:gd res.dot > res.png");
	system("gthumb res.png");
	return SUCCESS;
}
