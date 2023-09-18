#include "shell.h"

/**
 * removeComment - removes everything after a '#' char
 * @s: user input string
 */
void removeComment(char *s)
{
	int i = 0;

	if (s[i] == '#')
		s[i] = '\0';
	while (s[i] != '\0')
	{
		if (s[i] == '#' && s[i - 1] == ' ')
			break;
		i++;
	}
	s[i] = '\0';
}

/**
 *removeNewline - removes new line from a string
 *@s: user input string
 */
void removeNewline(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			break;
		i++;
	}
	s[i] = '\0';
}
