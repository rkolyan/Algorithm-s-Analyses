#ifndef _TYPES_MACR_FUNCS_H_
#define _TYPES_MACR_FUNCS_H_

typedef unsigned char type_t;

typedef struct stack_element
{
	int vartice_count;
	int *clique;
	struct stack_element *next;
} stack_element_t;

typedef struct vertice
{
	int num;
	int kol_of_vert;
	int *numbers_array;
} vertice_t;

/*
typedef struct vertice
{
	int num;
	int kol_of_vert1;
	struct vertice **mas1;
	int *masr1;
	int kol_of_vert2;
	struct vertice **mas2;
	int *masr2;
} vertice_t;

typedef struct mas_vertice
{
	int kol;
	vertice_t *mas[kol];
} mas_vertice_t;

typedef struct list_element
{
	void *data;
	struct list_element *next;
} list_element_t;

int *input_matrice(FILE *f, int kol);
int fill_mas_of_vertice(int **mas, mas_vertice_t *masv);
int find_shortest(vertice_t *vertice1, vertice_t *vertice2);
*/

#endif
