#include <stdio.h>
#include <string.h>
#include "io.h"

FILE *files[4] = {NULL};
 
static void reverse(char *s)
{
    int i = 0, j = 0;
    char c = '\0';

    for (i = 0, j = strlen(s)-1; i<j; i++, j--)
	{
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static void itoa(int n, char *s)
{
    int i = 0, sign = 0;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
	{
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

error_t open_files(int threads_count)
{
	char buffer[11] = {'\0'};
	itoa(threads_count, buffer + 2);
	if (threads_count < 10)
		strcpy(buffer + 3, ".txt");
	else if (threads_count < 100)
		strcpy(buffer + 4, ".txt");
	else if (threads_count < 1000)
		strcpy(buffer + 5, ".txt");
	else
		strcpy(buffer + 6, ".txt");
	buffer[0] = 's';
	buffer[1] = 'o';
	files[0] = fopen(buffer, "w");

	buffer[1] = 't';
	files[1] = fopen(buffer, "w");

	buffer[0] = 'v';
	buffer[1] = 'o';
	files[2] = fopen(buffer, "w");

	buffer[1] = 't';
	files[3] = fopen(buffer, "w");
	return SUCCESS;//TODO: Add protection
}

error_t write_in_files(clock_t value1, clock_t value2, clock_t value3, clock_t value4)
{
	fprintf(files[0], "%ld", value1);//Время однопоточной версии обычного умножения
	fprintf(files[1], "%ld", value2);//Время многопоточной версии обычного умножения
	fprintf(files[2], "%ld", value3);//Время однопоточной версии умножения методом Винограда
	fprintf(files[3], "%ld", value4);//Время многопоточной версии умножения методом Винограда
	return SUCCESS;
}

error_t close_files(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (files[i])
			fclose(files[i]);
	}
	return SUCCESS;
}


