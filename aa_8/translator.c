#include <stdio.h>

char is_other(char *string)
{
	for (int i = 0; string[i]; i++)
	{
		if (string[i] == '-' || string[i] == ' ')
			return 1;
	}
	return 0;
}

int main(void)
{
	char string[500] = {'\0'};
	FILE *file1 = fopen("ENRUS.TXT", "r");
	FILE *file2 = fopen("EN.TXT", "w");
	while(fgets(string, 500, file1))
	{
		if (string[0] <= 'z' && string[0] >= 'a' && !is_other(string))
			fputs(string, file2);
	}
	fclose(file2);
	fclose(file1);
	return 0;
}
