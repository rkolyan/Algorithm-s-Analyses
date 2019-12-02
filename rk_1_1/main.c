#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "types_macroses.h"

int main(int argc, char **argv)
{
	type_t *array = NULL;
	FILE *f;
	int kol = 0;
	vertice_t1 **varray = NULL;
	stack_element_t *head = NULL;

	if (argc != 2)
		return ERROR;
	f = fopen(argv[1], "r");
	kol = create_array_from_file(f, &array);
	fclose(f);
	varray = create_array_of_vertices(array, kol);
	free(array);
	create_file(varray, kol);
	for (int i = 1; i <= kol; i++)
	{
		fill_stack(varray[i - 1], &head);
		print_not_connected(&head, kol, i);
		remove_stack(&head);
	}
	destroy_graph(varray, kol);
	system("dot -Tpng:gd res.dot > res.png");
	
	pid_t childpid = fork();
	if (childpid == 0)
		execl("/usr/bin/gthumb", "gthumb", "res.png");
	return SUCCESS;
}
