#include "aco.h"
#include "notaco.h"
#include "func_memory.h"
#include "io.h"
#include "parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argument_count, char **arguments) 
{
	FILE *file = NULL;
	way_t *way1 = NULL, *way2 = NULL;
	way_t *ants = NULL;
	double **distance_matrix = NULL, **pheromone_matrix = NULL, **attraction_matrix = NULL;
	int vertice_count = 0, ant_count = 20;
	parameters_t parameters;

	if (argument_count != 2)
	{
		printf("Неккоректный ввод\nВведите ./app.exe FILENAME\nFILENAME - имя входного файла с матрицей\n");
		return 0;
	}
	file = fopen(arguments[1], "r");
	if (!file)
	{
		printf("Нет такого файла!\n");
		return 0;
	}
	input_matrix_from_file(&distance_matrix, &vertice_count, file);
	fclose(file);
	input_parameters(&parameters);
	input_integer(&ant_count, "количество муравьев", 1);

	//Инициализируем все ресурсы
	initialize_way(&way1);
	initialize_way(&way2);
	initialize_matrix(&pheromone_matrix, vertice_count);
	initialize_matrix(&attraction_matrix, vertice_count);
	initialize_ants(&ants, ant_count);

	srand(time(NULL));

	//Ищем пути различными способами
	puts("Результат работы муравьиного алгоритма:");
	find_commivoyager_way_aco(distance_matrix, pheromone_matrix, attraction_matrix, vertice_count, ants, ant_count, &parameters, way2);
	print_way(way2);

	puts("Результат работы алгоритма использующий полный перебор:");
	find_commivoyager_way_brute_force(distance_matrix, vertice_count, way1);
	print_way(way1);

	// Освобождаем все ненужные ресурсы
	free_ants(&ants, ant_count);
	free_matrix(&attraction_matrix);
	free_matrix(&pheromone_matrix);
	free_matrix(&distance_matrix);
 
	// Освобождаем все оставшиеся ресурсы
	free_way(&way1);
	free_way(&way2);

	return 0;
}
