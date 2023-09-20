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
		if ((s[i] == '#') && (s[i - 1] == ' '))
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

/**
 * space - f
 * @s: char
 * @whitespace: int
 * @i: int
 * Return: int
*/
int space(char *s, int whitespace, int i)
{
	s[_strcspn(s, "\n")] = '\0';
	whitespace = 1;
	for (i = 0; s[i] != '\0'; i++)
	{
		if ((unsigned char)s[i] != ' ')
		{
			whitespace = 0;
			break; }
	}
	return (whitespace);
}

/**
 * splitCommands - split the string by ;
 * @command: the string to be splited
 * @delim: the seperator like " " or ";"
 * Return: the commmads
*/
char **splitCommands(char *command, const char *delim)
{
	int num_commands = 0;
	char **commands = malloc(sizeof(char *) * 10);
	char *token = _strtok(command, delim);

	while (token != NULL)
	{
		commands[num_commands++] = token;
		token = _strtok(NULL, delim);
	}
	commands[num_commands] = NULL;

	return (commands);
}

/**
 * check_substring - check if substring exists in string
 * @str: the string
 * @substring: the substring
 * Return: 1 if the substring exists in string
 * or 0 if the substring doesn't exist in string
*/
int check_substring(char *str, char *substring)
{
	int i;

	for (i = 0; i < (int)_strlen(str) - (int)_strlen(substring) + 1; i++)
	{
		if (_strncmp(str + i, substring, _strlen(substring)) == 0)
			return (1);
	}
	return (0);
}
