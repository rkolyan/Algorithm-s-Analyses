#include <stdarg.h>

unsigned int find_minimum(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	unsigned int minimum = 0, tmp = 0;
	minimum--;
	for (int i = 0; i < n; i++)
	{
		tmp = va_arg(ap, unsigned int);
		minimum = tmp < minimum ? tmp : minimum;
	}
	return minimum;
}
