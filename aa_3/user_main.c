#include <stdlib.h>
#include <string.h>
#include "func_sort.h"
#include "io.h"

int main(void)
{
	int length = 0;
	type_t *array1 = NULL, *array2 = NULL, *array3 = NULL;
	
	//1)Create array
	write_size_of_array(&length);
	array1 = calloc(length, sizeof(type_t));
	array2 = calloc(length, sizeof(type_t));
	array3 = calloc(length, sizeof(type_t));
	write_into_array(array1, length);
	memcpy(array2, array1, length * sizeof(type_t));
	memcpy(array3, array1, length * sizeof(type_t));
	putchar('\n');
	print_array(stdout, array1, length);
	putchar('\n');
	
	//2)Get result, using min and max sorting
	sort_min_max(array1, length);
	print_array(stdout, array1, length);
	
	//3)Get result, using bubble sorting
	sort_bubble(array2, length);
	print_array(stdout, array2, length);

	//4)Get result, using shaker sorting
	sort_shaker(array3, length);
	print_array(stdout, array3, length);
	putchar('\n');
	
	//4)Free all memory and exit
	free(array1);
	free(array2);
	free(array3);
	return 0;
}
