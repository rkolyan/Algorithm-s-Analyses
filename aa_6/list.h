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
error_t merge_lists(list_t **head1, list_t **head2, list_t **head_result);
error_t remove_last_from_list(list_t **head);
error_t copy_list(list_t *source, list_t **destination);
int in_list(list_t *head, int num);
void print_list(list_t *head);

#endif
