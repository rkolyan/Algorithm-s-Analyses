#include <stdlib.h>
#include <string.h>
#include "minimum.h"
#include "func_distance.h"

//Recursive Levenstein
error_t find_levenstein_distance_recursive(char *s1, char *s2, int length1, int length2, unsigned *result)
{
	if (!s1 || !s2 || !length1 || !length2 || !result)
		return ERROR_INPUT;

	if (length1 == 1 || length2 == 1)
	{
		*result = s1[length1 - 1] == s2[length2 - 1] ? 0 : 1;
		*result += abs(length2 - length1);
		return SUCCESS;
	}

	short tmp = 0;
	if (s1[length1 - 1] != s2[length2 - 1])
		tmp = 1;

	find_levenstein_distance_recursive(s1, s2, length1 - 1, length2, result);
	(*result)++;
	unsigned tmp_result = 0;
	find_levenstein_distance_recursive(s1, s2, length1, length2 - 1, &tmp_result);
	*result = find_minimum(2, *result, tmp_result + 1);
	find_levenstein_distance_recursive(s1, s2, length1 - 1, length2 - 1, &tmp_result);
	*result = find_minimum(2, *result, tmp_result + tmp);
	return SUCCESS;
}
