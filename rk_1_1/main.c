#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "matrix.h"
#include "vertices.h"
#include "clique.h"

int main(int argc, char **argv)
{
	type_t *matrix = NULL;
	FILE *f;
	int count = 0;
	vertice_t *varray = NULL;
	clique_stack_element_t *clique_stack = NULL;

	if (argc != 2)
		return ERROR_INPUT;
	f = fopen(argv[1], "r");
	if (!f)
		return ERROR_INCORRECT;
	create_matrix_from_file(f, &matrix, &count);
	fclose(f);
	create_vertices(matrix, count, &varray);
	find_cliques(varray, count, &clique_stack);
	print_cliques(varray, count, clique_stack);
	remove_clique_stack(&clique_stack);
	free(matrix);
	create_output_graph_file(varray, count);
	remove_vertices(&varray, &count);
	system("dot -Tpng:gd res.dot > res.png");
	system("gthumb res.png");
	return SUCCESS;
}
