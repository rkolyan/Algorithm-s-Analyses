#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "error_codes.h"
#include "find_control_graph.h"
#include "func_file.h"
//#include "find_operations_history.h"
//#include "find_informational_graph.h"
//#include "find_informational_history.h"

int main(int argument_count, char **arguments)
{
	if (argument_count != 2)
	{
		puts("Некорректная запись!");
		puts("Вы должны ввести в терминал команду вида:");
		puts("./app.exe <FILE_WITH_CODE>");
		return SUCCESS;
	}
	FILE *file = NULL;
	file = fopen(arguments[1], "r");
	if (!file)
	{
		printf("Файла с именем %s не существует!\n", arguments[1]);
		return SUCCESS;
	}

	graph_vertice_t *graph = NULL;
	int vertice_count = 0;
	char **strings = NULL;

	//TODO:Построить граф управления и записать результат в файл result1.dot
	input_from_file(file, &strings, &vertice_count);
	initialize_graph(&graph, vertice_count);
	find_control_graph(strings, vertice_count, graph);
	create_dot_file("result1.dot", graph, vertice_count);
	free_graph(&graph, vertice_count);
	/*
	pid_t current;
	current = fork();
	if (current == 0)
	{
		execlp("dot", "-Tsvg", "result1.dot", ">", "result1.png");
		//TODO:Draw graphs
	}
	*/
	//TODO:Построить операционную историю > result2.dot
	//TODO:Что делать в случае с историями, неужели списки?
	/*
	current = fork();
	if (current == 0)
	{
		execlp("dot", "-Tsvg", "result2.dot", ">", "result2.png");
		//TODO:Draw graphs
	}
	//TODO:Построить информационный граф > result3.dot
	initialize_graph(&graph, vertice_count);
	//find_informational_graph(strings, vertice_count, &graph);
	create_dot_file("result3.dot", graph, vertice_count);
	free_graph(&graph, vertice_count);
	current = fork();
	if (current == 0)
	{
		execlp("dot", "-Tsvg", "result3.dot", ">", "result3.png");
		//TODO:Draw graphs
	}
	//TODO:Построить информационную историю > result4.dot
	//TODO:Что делать в случае с историями, неужели списки?
	current = fork();
	if (current == 0)
	{
		execlp("dot", "-Tsvg", "result4.dot", ">", "result4.png");
		//TODO:Draw graphs
	}
	*/
	//TODO:Delete all strings
	fclose(file);
	return SUCCESS;
}
