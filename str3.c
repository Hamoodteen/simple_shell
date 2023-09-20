#include "shell.h"

/**
 * check_substring - check if substring exists in string
 * @str: the string
g * @substring: the substring
 * Return: 1 if the substring exists in string
 * or 0 if the substring doesn't exist in string
*/
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
