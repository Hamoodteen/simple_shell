#include "shell.h"


int check_substring(char *str, char *substring)
{
	int i;

	for (i = 0; i < (int)_strlen(str) - (int)_strlen(substring) + 1; i++)
	{
		if (_strncmp(str + i, substring, _strlen(substring)) == 0)
		{
		return (1);
		}
	}
	return (0);
}
