#ifndef LIST_H
#define LIST_H

#include "error_codes.h"

typedef struct list
{
	int num;
	struct list *next;
	struct list *previous;
} list_t;

error_t add_element_to_list(list_t **head, int num);
error_t delete_list(list_t **head);
void print_list(list_t *head);

#endif
